"""
Copyright 2023-2025 Cypress Semiconductor Corporation (an Infineon company)
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
from .advanced_validator import AdvancedValidatorPse84A0
from .maps.asset_map import AssetMapPse84
from .maps.memory_map import MemoryMapPse84
from .maps.register_map import RegisterMapPse84
from .policy_parser.policy_parser import PolicyParser
from .policy_version_validator import PolicyVersionValidator
from .policy_validator import PolicyValidatorPSE84A0
from .cert_pse84 import CertificateStrategyPSE84
from ..common.mxs22 import (
    TokenMXS22,
    ProjectInitializerMXS22, RamAppLoaderMXS22, ProvisioningPacketMXS22,
    ProvisioningMXS22, VersionProviderMXS22, SiliconDataReaderMXS22
)
from ..common.mxs22.data import RamAppStatusMXS22
from ..common.mxs22.device_integrity_mxs22 import DeviceIntegrityMXS22
from ...core import TargetBuilder
from ...core.enums import KeyAlgorithm


class PSE84Builder(TargetBuilder):
    """ PSoC Edge E84 A0 target builder """

    def get_default_policy(self):
        return None

    def get_ocds(self):
        return ['openocd', 'serial']

    def get_ocd_config(self):
        return {
            'openocd': {
                'variables': 'set ENABLE_CM33 0; set ENABLE_CM55 0',
                'interface': 'kitprog3',
                'before_init': '',
                'after_init': 'reset init; targets'
            }
        }

    def get_memory_map(self):
        return MemoryMapPse84()

    def get_register_map(self):
        return RegisterMapPse84()

    def get_policy_parser(self, policy):
        return PolicyParser(policy)

    def get_policy_validator(self, policy_parser, memory_map):
        version_validator = PolicyVersionValidator(policy_parser)
        dependency_validator = AdvancedValidatorPse84A0(policy_parser)
        return PolicyValidatorPSE84A0(policy_parser, version_validator, None,
                                      dependency_validator)

    def get_policy_filter(self, policy_parser):
        """N/A for PSoC Edge E84"""

    def get_provisioning_strategy(self):
        return ProvisioningMXS22()

    def get_provisioning_packet_strategy(self, policy_parser):
        return ProvisioningPacketMXS22(policy_parser, AssetMapPse84())

    def get_entrance_exam(self):
        return DeviceIntegrityMXS22

    def get_voltage_tool(self):
        return None

    def get_key_reader(self):
        return None

    def get_project_initializer(self):
        return ProjectInitializerMXS22

    def get_silicon_data_reader(self):
        return SiliconDataReaderMXS22

    def get_key_algorithms(self):
        return [
            KeyAlgorithm.ECDSA_P256, KeyAlgorithm.ECDSA_P384,
            KeyAlgorithm.RSA2048, KeyAlgorithm.RSA4096,
            KeyAlgorithm.AES128, KeyAlgorithm.AES256
        ]

    def get_sign_tool(self):
        return None

    def get_key_source(self, **kwargs):
        return None

    def get_bootloader_provider(self):
        return None

    def get_version_provider(self):
        return VersionProviderMXS22

    def get_debug_certificate(self):
        return TokenMXS22()

    def get_policy_generator(self, policy_parser):
        return None

    def get_test_packages(self):
        return {
            'testapps': {
                'package': 'testapps_explorer', 'flow_name': 'testapps'
            },
            'testapps_si': {
                'package': 'testapps_explorer', 'flow_name': 'testapps_si'
            }
        }

    def get_certificate_strategy(self):
        return CertificateStrategyPSE84()

    def get_app_loader(self):
        return RamAppLoaderMXS22(RamAppStatusMXS22())

    def get_silicon_id(self):
        """Gets the target silicon ID"""
        return None
