################################################################################
# \file defines.mk
#
# \brief
# Defines, needed for the PSOC(TM) Edge build recipe.
#
################################################################################
# \copyright
# (c) 2021-2025, Cypress Semiconductor Corporation (an Infineon company) or
# an affiliate of Cypress Semiconductor Corporation. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

ifeq ($(WHICHFILE),true)
$(info Processing $(lastword $(MAKEFILE_LIST)))
endif

include $(MTB_TOOLS__RECIPE_DIR)/make/recipe/defines_common.mk

ifneq ($(OTA_SUPPORT),)
# OTA post-build script needs python.
CY_PYTHON_REQUIREMENT=true
endif

################################################################################
# General
################################################################################
_MTB_RECIPE__PROGRAM_INTERFACE_SUPPORTED:=KitProg3 JLink
#
# Compactibility interface for this recipe make
#
MTB_RECIPE__INTERFACE_VERSION:=2
MTB_RECIPE__EXPORT_INTERFACES:=3 4

MTB_RECIPE__NINJA_SUPPORT:=1 2

ifeq ($(MTB_TYPE),PROJECT)
_MTB_RECIPE__IS_MULTI_CORE_APPLICATION:=true
endif

#
# List the supported toolchains
#
ifdef CY_SUPPORTED_TOOLCHAINS
MTB_SUPPORTED_TOOLCHAINS?=$(CY_SUPPORTED_TOOLCHAINS)
else
MTB_SUPPORTED_TOOLCHAINS?=GCC_ARM IAR ARM LLVM_ARM
endif

ifeq ($(TOOLCHAIN),ARM)
PC_SYMBOL=__main
SP_SYMBOL=Image$$$$ARM_LIB_STACK$$$$ZI$$$$Limit
else ifeq ($(TOOLCHAIN),IAR)
PC_SYMBOL=Reset_Handler
SP_SYMBOL=CSTACK$$$$Limit
else ifeq ($(TOOLCHAIN),GCC_ARM)
PC_SYMBOL=Reset_Handler
SP_SYMBOL=__StackTop
endif

#
# Define the default device mode
#
VCORE_ATTRS?=SECURE

# TODO(OMAK): Need to revise when MPNs are available
ifeq ($(MTB_RECIPE__CORE),CM33)
ifneq ($(filter NON_SECURE,$(VCORE_ATTRS)),)
_MTB_RECIPE__START_FLASH=0x00000000
else
_MTB_RECIPE__START_FLASH=0x10000000
endif
else
_MTB_RECIPE__START_FLASH=0x00000000
endif

#
# Core specifics
#
_MTB_RECIPE__OPENOCD_SECOND_RESET_TYPE=
_MTB_RECIPE__OPENOCD_RUN_RESTART_CMD_DEBUG_ECLIPSE=
_MTB_RECIPE__OPENOCD_RUN_RESTART_CMD_ATTACH_ECLIPSE=
_MTB_RECIPE__OPENOCD_EXTRA_PORT_ECLIPSE=
_MTB_RECIPE__OPENOCD_CORE=
_MTB_RECIPE__OPENOCD_CORE_PORT=
_MTB_RECIPE__JLINK_GDB_PORT=
_MTB_RECIPE__JLINK_SWO_PORT=
_MTB_RECIPE__JLINK_TELNET_PORT=

#
# Architecure specifics
#
_MTB_RECIPE__OPENOCD_CHIP_NAME:=cat1d
_MTB_RECIPE__JLINK_DEVICE_CM0_CFG:=PSE84x_CM0p
_MTB_RECIPE__OPENOCD_DEVICE_CFG:=infineon/pse84xgxs2.cfg
ifneq ($(filter EPC4,$(DEVICE_$(DEVICE)_FEATURES)),)
_MTB_RECIPE__OPENOCD_DEVICE_CFG:=infineon/pse84xgxs4.cfg
endif
ifeq (EXPLORER_A0,$(_MTB_RECIPE__DEVICE_DIE))
_MTB_RECIPE__JLINK_DEVICE_CM0_CFG:=PSE84x_A0_CM0p
_MTB_RECIPE__OPENOCD_DEVICE_CFG:=infineon/pse84_a0.cfg
endif
ifeq ($(APPTYPE), ram)
_MTB_RECIPE__APPTYPE_DIR:=ram
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=
_MTB_RECIPE__PREBUILT_SECURE_APP=secure_region.hex
_MTB_RECIPE__PREBUILT_CM0_IMAGE=cm0_boot_app.elf
ifeq ($(BITFILE_PROVISIONED),false)
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=virgin
else ifeq ($(BITFILE_PROVISIONED),true)
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=_normal
else
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=normal
endif
else #ifeq ($(APPTYPE), flash)
_MTB_RECIPE__APPTYPE_DIR:=flash
# Generate specific configs for bare bitfile with MVP bootrom
ifeq ($(BITFILE_PROVISIONED),false)
_MTB_RECIPE__PREBUILT_SECURE_APP=secure_region_rram.bin
_MTB_RECIPE__PREBUILT_CM0_IMAGE=cm0_boot_app_rram.elf
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=virgin
else ifeq ($(BITFILE_PROVISIONED),true)
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=_normal
_MTB_RECIPE__PREBUILT_SECURE_APP=secure_region.hex
else
_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR:=normal
endif
endif

# Always use secure alias for programming PSE84x_CM33_S
_MTB_RECIPE__JLINK_DEVICE_CFG_PROGRAM:=PSE84xGxS2_CM33_S
ifneq ($(filter EPC4,$(DEVICE_$(DEVICE)_FEATURES)),)
_MTB_RECIPE__JLINK_DEVICE_CFG_PROGRAM:=PSE84xGxS4_CM33_S
endif
ifeq (EXPLORER_A0,$(_MTB_RECIPE__DEVICE_DIE))
_MTB_RECIPE__JLINK_DEVICE_CFG_PROGRAM:=PSE84x_A0_CM33_S
else
# Explorer B0
ifneq ($(filter PSE84_PSVP,$(DEFINES)),)
_MTB_RECIPE__JLINK_DEVICE_CFG_PROGRAM:=PSE84x_PSVP_CM33_S
endif
endif

ifeq ($(MTB_RECIPE__CORE),CM33)
# CM33 core
_MTB_RECIPE__JLINK_DEVICE_CFG:=PSE84xGxS2_CM33_S
ifneq ($(filter EPC4,$(DEVICE_$(DEVICE)_FEATURES)),)
_MTB_RECIPE__JLINK_DEVICE_CFG:=PSE84xGxS4_CM33_S
endif
ifeq (EXPLORER_A0,$(_MTB_RECIPE__DEVICE_DIE))
_MTB_RECIPE__JLINK_DEVICE_CFG:=PSE84x_A0_CM33_S
else
# Explorer B0
ifneq ($(filter PSE84_PSVP,$(DEFINES)),)
_MTB_RECIPE__JLINK_DEVICE_CFG:=PSE84x_PSVP_CM33_S
endif
endif
ifneq ($(filter NON_SECURE,$(VCORE_ATTRS)),)
_MTB_RECIPE__OPENOCD_RESET_TARGET:=cm33_ns
else
_MTB_RECIPE__OPENOCD_RESET_TARGET:=cm33
endif
else
# CM55 core
_MTB_RECIPE__OPENOCD_RESET_TARGET:=cm55
_MTB_RECIPE__JLINK_DEVICE_CFG:=PSE84x_CM55
ifeq (EXPLORER_A0,$(_MTB_RECIPE__DEVICE_DIE))
_MTB_RECIPE__JLINK_DEVICE_CFG:=PSE84x_A0_CM55
endif
endif # MTB_RECIPE_CORE

ifneq ($(filter PSE84_PSVP,$(DEFINES)),)
_MTB_RECIPE__OPENOCD_BOARD=set BOARD psvp
endif

# MVE support
# If MVE is not available on device then MVE_SELECT=NO_MVE. 
# If MVE is available on device and VFP_SELECT=softfloat, then MVE_SELECT=MVE-I, 
# else MVE_SELECT=<empty> (MVE-F mode).
ifeq ($(filter $(CORE_NAME)_MVE_PRESENT,$(DEVICE_$(DEVICE)_FEATURES)),)
MVE_SELECT?=NO_MVE
else
ifeq ($(VFP_SELECT),softfloat)
MVE_SELECT?=MVE-I
else
MVE_SELECT?=
endif
endif
