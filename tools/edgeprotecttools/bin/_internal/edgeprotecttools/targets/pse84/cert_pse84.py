"""
Copyright 2024-2025 Cypress Semiconductor Corporation (an Infineon company)
or an affiliate of Cypress Semiconductor Corporation. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
import logging
import os
from datetime import datetime

from cbor import cbor
from cryptography.hazmat.primitives import serialization
from cwt import VerifyError

from ..common.mxs22.enums import DeviceResponse
from ..common.mxs22.version_provider_mxs22 import VersionProviderMXS22
from ...core.cose import Cose
from ...core.key_handlers import load_public_key
from ...core.key_handlers.ec_handler import ECHandler
from ..common.mxs22 import CertificateStrategyMXS22

logger = logging.getLogger(__name__)


class CertificateStrategyPSE84(CertificateStrategyMXS22):
    """Create certificates for PSE84 family"""

    def create_certificate(self, filename, encoding, overwrite, **kwargs):
        """Creates certificate in CBOR format"""
        private_keys = kwargs.get('key_path')
        if private_keys and all(private_keys):
            if not isinstance(private_keys, tuple):
                private_keys = (private_keys, )
            for key in private_keys:
                self.key_validator.validate_private_key(key)

        dev_cert = kwargs.get('dev_cert').lower()
        if dev_cert in ('cert', 'oem') and kwargs.get('template'):
            return self.create_certificate_from_template(filename, **kwargs)
        if dev_cert == 'device':
            return self._create_device_certificate(filename, **kwargs)
        if dev_cert == 'oem':
            return self._create_oem_certificate(filename, **kwargs)
        if dev_cert == 'device_integrity':
            return self._device_integrity_cert(filename, **kwargs)
        raise ValueError(f"Invalid type of ifx cbor certificate "
                         f"'{dev_cert}'")

    def create_csr(self, output, key_path, **kwargs):
        """Creates CSR in CBOR format"""
        template = kwargs.get('template')
        for key_item in key_path:
            if key_item:
                self.key_validator.validate_private_key(key_item)
        if template:
            return self.create_certificate_from_template(
                output, key_path=key_path, **kwargs)
        return self._create_oem_csr(output, key_path, **kwargs)

    def _create_device_certificate(self, output, **kwargs):
        """
        Creates IFX device certificate from the CSR
        @param output:Path where to save the created
                        certificate
        @param kwargs:
            :csr: CSR path
            :key: Private key path to sign certificate
            :algorithm: Signature algorithm type
        @return: Certificate object
        """
        csr_path = kwargs.get('csr')
        _, csr_data = self.load_cert(csr_path)
        response = csr_data.get(DeviceResponse.DEV_RSP)
        dev_csr_cbor = response.get(DeviceResponse.DEV_ID_CERT)
        cose_packet = cbor.loads(dev_csr_cbor)
        csr = cbor.loads(cose_packet.value[2])
        csr_raw_key = csr.get('DICE_DEVICE_ID_PUBLIC_KEY')
        csr_pub_key = ECHandler.populate_public_key(csr_raw_key)

        try:
            self._decode_verify(dev_csr_cbor, csr_pub_key)
            logger.info('Device CSR verification success')
        except VerifyError:
            logger.error('Failed to verify Device_CSR packet')

        die_id = csr.get('DIE_ID')
        fields = {
            'lot': int.from_bytes(die_id[:3], byteorder='little'),
            'wafer': int.from_bytes(die_id[3:4], byteorder='little'),
            'x': int.from_bytes(die_id[4:5], byteorder='little'),
            'y': int.from_bytes(die_id[5:6], byteorder='little'),
            'sort': int.from_bytes(die_id[6:7], byteorder='little'),
            'day': int.from_bytes(die_id[7:8], byteorder='little'),
            'month': int.from_bytes(die_id[8:9], byteorder='little'),
            'year': int.from_bytes(die_id[9:10], byteorder='little'),
        }
        rom_boot = VersionProviderMXS22.convert_fw_version(
            csr.get('ROM_BOOT_VERSION'))
        rram_boot = VersionProviderMXS22.convert_fw_version(
            csr.get('RRAM_BOOT_VERSION'))
        family_id = int.from_bytes(csr.get('FAMILY_ID'), byteorder='little')
        rev_id = int.from_bytes(csr.get('REVISION_ID'), byteorder='little')

        logger.info('Device CSR:')
        logger.info('- DICE_DEVICE_ID_PUBLIC_KEY: %s',
                    csr.get('DICE_DEVICE_ID_PUBLIC_KEY').hex())
        logger.info('- DIE_ID:')
        for n, v in fields.items():
            logger.info('\t - %s: %s', n, v)
        logger.info('- ROM_BOOT_VERSION: %s', rom_boot)
        logger.info('- RRAM_BOOT_VERSION: %s', rram_boot)
        logger.info('- FAMILY_ID: %s', hex(family_id))
        logger.info('- REVISION_ID: %s', hex(rev_id))

        cbor_cert = cbor.dumps(csr)
        key = kwargs.get('key_path')
        algorithm = kwargs.get('algorithm')
        if key:
            cbor_cert = Cose.cose_sign1(cbor_cert, key)
        elif algorithm:
            cbor_cert = Cose.prepare_hsm_sign1(cbor_cert, algorithm)
        if output:
            self._save_cbor(cbor_cert, output, 'IFX Device certificate')
        return cbor_cert

    def _create_oem_certificate(self, output, **kwargs):
        """
        Creates IFX OEM certificate from the CSR
        @param output:Path where to save the created certificate
        @param kwargs:
                :csr_path: The path where to be got CSR
                :date: The date of the OEM certificate creation
                :cert_id: A unique S/N for this certificate
                :key: Private key path to sign certificate
                :signer_id: The unique ID of the signer
                :algorithm: Signature algorithm type
        @return: Certificate object
        """
        csr = self.load_bin(kwargs.get('csr'))
        cbor_info = cbor.loads(csr)
        csr_info = cbor.loads(cbor_info.value[2])
        pub_keys = (csr_info.get('public_key_0'), csr_info.get('public_key_1'))
        cbor_d = None
        for key in pub_keys:
            if key:
                pubkey = ECHandler.populate_public_key(key)
                cbor_d = self._decode_verify(csr, pubkey)
        decoded_cbor = cbor.loads(cbor_d)
        date = self.utcnow() if kwargs.get('date') is None \
            else datetime.strptime(kwargs.get('date'), "%Y-%m-%dT%H:%M:%S")
        json_cert = {'public_key_0': decoded_cbor.get('public_key_0')}
        pub_key_1 = decoded_cbor.get('public_key_1')
        if pub_key_1:
            json_cert['public_key_1'] = pub_key_1
        json_cert['date'] = date.strftime("%Y-%m-%d %H:%M:%S")
        json_cert['id'] = kwargs.get('cert_id')
        json_cert['oem'] = decoded_cbor['oem']
        json_cert['project'] = decoded_cbor['project']
        json_cert['project_number'] = decoded_cbor['project_number']
        cert_type = str(decoded_cbor['certificate_type']).lower()
        json_cert['certificate_type'] = cert_type
        json_cert['signer_id'] = kwargs.get('signer_id')
        key = kwargs.get('key_path')
        return self._save_oem_cert(json_cert, key, output, **kwargs)

    def _create_oem_csr(self, output, key_path, **kwargs):
        """Creates OEM CSR
        @param output: Path to save CSR
        @param key_path: Tuple of paths to the public_primary, public_secondary,
            private_primary and private_secondary keys
        @param kwargs:
            :date: The date of the OEM CSR creation
            :oem: The OEM name
            :project: The OEM project name
            :project_number: The OEM project number
            :cert_type: Certificate type Development or Production
            :algorithms: A tuple of used algorithm types
        @return: CBOR CSR
        """
        cert_type = str(kwargs.get('cert_type')).lower()
        if cert_type not in ('development', 'production'):
            raise ValueError(f"Unsupported certificate type '{cert_type}'")

        public_key = []
        for item in (kwargs.get('public_key_0'), kwargs.get('public_key_1')):
            if item:
                self.key_validator.validate_public_key(item)
                key_data = load_public_key(item)
                public_key.append(self._public_x962_encoded(key_data))
        if len(public_key) < 2 and cert_type == 'production':
            raise ValueError('Production-type CSR must contain two public keys')

        date = self.utcnow() if kwargs.get('date') is None \
            else datetime.strptime(kwargs.get('date'), "%Y-%m-%dT%H:%M:%S")
        json_csr = {}
        for idx, pub_key in enumerate(public_key):
            json_csr.update({f'public_key_{idx}': pub_key})
        json_csr['date'] = date.strftime("%Y-%m-%d %H:%M:%S")
        json_csr['oem'] = kwargs.get('oem')
        json_csr['project'] = kwargs.get('project')
        json_csr['project_number'] = kwargs.get('project_number')
        json_csr['certificate_type'] = cert_type
        return self._save_oem_csr(json_csr, key_path, output, **kwargs)

    def _read_extensions_template(self):
        """Reads extensions and adds to the CSR"""
        extensions = os.path.join(
            os.path.dirname(__file__), 'packets', 'csr_extensions.json'
        )
        return self.load_json(extensions)

    @staticmethod
    def _save_encoded(csr_path, csr_data, encoding='PEM'):
        """Saves generated CSR or certificate with PEM or DER encoding"""
        if encoding.upper() == 'PEM':
            enc = serialization.Encoding.PEM
        elif encoding.upper() == 'DER':
            enc = serialization.Encoding.DER
        else:
            raise ValueError(f'Invalid CSR encoding {encoding}')

        with open(csr_path, 'wb') as file:
            file.write(csr_data.public_bytes(enc))

    def _save_oem_csr(self, json_csr, key_path, output, **kwargs):
        cbor_csr = cbor.dumps(json_csr)
        algorithms = kwargs.get('algorithms')
        if key_path and all(key_path):
            cbor_csr = Cose.cose_sign(cbor_csr, key_path)
        elif key_path[0] and key_path[1] is None:
            cbor_csr = Cose.cose_sign1(cbor_csr, key_path[0])
        elif algorithms and all(algorithms):
            hsm_structs = Cose.prepare_hsm_sign(cbor_csr, algorithms)
            if algorithms[0] != algorithms[1]:
                if output:
                    csr_path, ext = os.path.splitext(output)
                    for itm, alg in zip(hsm_structs, algorithms):
                        itm_path = csr_path + '_' + alg + ext
                        self._save_cbor(itm, itm_path,
                                        'OEM CSR for HSM signing')
                return hsm_structs
            if output:
                self._save_cbor(hsm_structs[-1], output,
                                'OEM CSR for HSM signing')
            return hsm_structs[-1]
        elif algorithms[0] and algorithms[1] is None:
            hsm_struct = Cose.prepare_hsm_sign1(cbor_csr, algorithms[0])
            if output:
                self._save_cbor(hsm_struct, output, 'OEM CSR for HSM signing')
            return hsm_struct

        if output:
            self._save_cbor(cbor_csr, output, 'OEM CSR')
        return cbor_csr

    def _save_oem_cert(self, json_cert, key_p, output, **kwargs):
        cbor_cert = cbor.dumps(json_cert)
        algorithm = kwargs.get('algorithm')
        if key_p:
            cbor_cert = Cose.cose_sign1(cbor_cert, key_p)
        elif algorithm:
            cbor_cert = Cose.prepare_hsm_sign1(cbor_cert, algorithm)
        if output:
            self._save_cbor(cbor_cert, output, 'IFX OEM certificate')
        return cbor_cert
