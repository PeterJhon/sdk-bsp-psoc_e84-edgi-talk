/*******************************************************************************
* File Name: mtb_syspm_callbacks_drivers.h
*
* Description:
* Implementation specific syspm-callbacks header file that pulls in all driver
* files that are applicable for this implementation.
*
********************************************************************************
* \copyright
* Copyright 2024-2024 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#pragma once


#if (MTB_SYSPM_CALLBACKS_AVAILABLE_DMA)
    #include "mtb_syspm_callbacks_dma.h"
#endif // (MTB_SYSPM_CALLBACKS_AVAILABLE_DMA)

#if (MTB_SYSPM_CALLBACKS_AVAILABLE_I2S_TDM)
    #include "mtb_syspm_callbacks_i2s_tdm.h"
#endif // (MTB_SYSPM_CALLBACKS_AVAILABLE_I2S_TDM)

#if (MTB_SYSPM_CALLBACKS_AVAILABLE_NVM)
    #include "mtb_syspm_callbacks_nvm.h"
#endif

#if defined(MTB_SYSPM_CALLBACKS_AVAILABLE_PDM_PCM)
    #include "mtb_syspm_callbacks_pdm_pcm.h"
#endif // defined(MTB_SYSPM_CALLBACKS_AVAILABLE_PDM_PCM)

#if (MTB_SYSPM_CALLBACKS_AVAILABLE_SCB_UART)
    #include "mtb_syspm_callbacks_scb_uart.h"
#endif // (MTB_SYSPM_CALLBACKS_AVAILABLE_SCB_UART)

#if (MTB_SYSPM_CALLBACKS_AVAILABLE_SMIF)
    #include "mtb_syspm_callbacks_smif.h"
#endif // (MTB_SYSPM_CALLBACKS_AVAILABLE_SMIF)

#if (MTB_SYSPM_CALLBACKS_AVAILABLE_TCPWM)
    #include "mtb_syspm_callbacks_tcpwm.h"
#endif
