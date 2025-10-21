# SE Runtime Services Utilities Library

## Changelog

### v1.0.0
Initial release
Known issues:
 - User can get IFX_SE_ERROR_INSUFFICIENT_STORAGE during import AES persistent keys


### v1.1.0
New Crypto API:
 - ifx_se_key_derivation_key_agreement
 - ifx_se_raw_key_agreement
New Attestation API:
 - ifx_se_set_shared_data
 - ifx_se_lock_shared_data
 - ifx_se_initial_attest_get_token
 - ifx_se_initial_attest_get_token_size
New features:
 - key owner support
 - read and check temperature before first TRNG
Critical fixes:
 - fixed IFX_SE_ERROR_INSUFFICIENT_STORAGE error for AES persistent keys


### Supported Software and Tools
This version of the SE Runtime Services Utilities was validated for compatibility with the following Software and Tools:

| Software and Tools                                                        | Version |
| :---                                                                      | :-----: |
| ModusToolbox Software Environment                                         | 3.3     |
| MTB CAT1 Peripheral Driver Library (PDL)                                  | 3.11.0  |
| GCC Compiler                                                              | 11.3.1  |
| IAR Compiler                                                              | 9.50.2  |
| ARM Compiler 6                                                            | 6.22    |

---
© Cypress Semiconductor Corporation (an Infineon company), 2023-2024.
