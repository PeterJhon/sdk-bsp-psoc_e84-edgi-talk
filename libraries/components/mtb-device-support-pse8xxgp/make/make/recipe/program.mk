################################################################################
# \file program.mk
#
# \brief
# This make file is called recursively and is used to build the
# resoures file system. It is expected to be run from the example directory.
#
################################################################################
# \copyright
# (c) 2018-2025, Cypress Semiconductor Corporation (an Infineon company) or
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

include $(MTB_TOOLS__RECIPE_DIR)/make/recipe/program_common.mk

_MTB_RECIPE__OPENOCD_DEBUG_PREFIX=$(_MTB_RECIPE__OPENOCD_CHIP_NAME).cm33 configure -rtos auto -rtos-wipe-on-reset-halt 1; gdb_breakpoint_override hard;

ifeq ($(TOOLCHAIN),A_Clang)
_MTB_RECIPE__OPENOCD_PROGRAM_IMG=$(MTB_RECIPE__LAST_CONFIG_DIR)/$(APPNAME).bin $(TOOLCHAIN_VECT_BASE_CM33)
else
_MTB_RECIPE__OPENOCD_SYMBOL_IMG=$(_MTB_RECIPE__LAST_CONFIG_TARG_FILE)
_MTB_RECIPE__OPENOCD_PROGRAM_IMG=$(_MTB_RECIPE__LAST_CONFIG_PROG_FILE)

endif

# Multi-core application programming: always use combined HEX image
ifneq ($(_MTB_RECIPE__APP_HEX_FILE),)
_MTB_RECIPE__OPENOCD_PROGRAM_IMG=$(_MTB_RECIPE__APP_HEX_FILE)
endif

# Use custom HEX image when PROG_FILE was provided by the user
ifneq ($(PROG_FILE),)
_MTB_RECIPE__OPENOCD_PROGRAM_IMG=$(PROG_FILE)
endif

ifneq ($(MTB_ERASE_EXT_MEM),)
# Extract address ranges from qspi_config.cfg
_MTB_RECIPE__JLINK_ERASE_EXT_MEM=$(shell awk '/^[^#]*addr/ { \
                          addr = strtonum("0x" substr($$3, 3)); \
                          size = strtonum("0x" substr($$5, 3)); \
                          end_addr = addr + size - 1; \
                          printf("Erase 0x%x, 0x%x|", addr, end_addr); \
                          }' $(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH)/qspi_config.cfg)
endif

ifeq ($(APPTYPE),ram)
_MTB_RECIPE__GDB_ARGS=$(MTB_TOOLS__RECIPE_DIR)/make/scripts/gdbinit_ram
_MTB_RECIPE__REGISTERS_CONFIGS=mww 0x52401240 0x80000000; mww 0x52401244 0x80000000; mww 0x52401248 0x80000000; \
								mww 0x52410070 0x00000010; mww 0x54004090 0x00000002; mww 0x54640008 0x0000001f; \
								mww 0x52413000 0x108; mww 0x54100000 0x108; mww 0x54101000 0x01010108; mww 0x54004110 0x00000001;
else
ifeq ($(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR), JLink)
_MTB_RECIPE__GDB_ARGS=$(MTB_TOOLS__RECIPE_DIR)/make/scripts/gdbinit_jlink
else
_MTB_RECIPE__GDB_ARGS=$(MTB_TOOLS__RECIPE_DIR)/make/scripts/gdbinit
endif #($(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR), JLink)
endif #($(APPTYPE),ram)

ifeq ($(BITFILE_PROVISIONED),true) # BITFILE_PROVISIONED=true for provisioned PSVP/MCU
_MTB_RECIPE__OPENOCD_ERASE=exit;
_MTB_RECIPE__OPENOCD_DEBUG=$(_MTB_RECIPE__OPENOCD_DEBUG_PREFIX) init; $(_MTB_RECIPE__REGISTERS_CONFIGS); halt;
_MTB_RECIPE__OPENOCD_PROGRAM=init; $(_MTB_RECIPE__REGISTERS_CONFIGS); halt; flash write_image erase $(_MTB_RECIPE__OPENOCD_PROGRAM_IMG); load_image $(_MTB_RECIPE__OPENOCD_PROGRAM_IMG); mww 0x52261000 0x34000400; mww 0x52260004 0x05FA0000; exit;
else ifeq ($(BITFILE_PROVISIONED),false) # BITFILE_PROVISIONED=false for bare bitfile with MVP bootrom
_MTB_RECIPE__APP_LOAD_ADDR=0x24080000
_MTB_RECIPE__APP_SP=$(_MTB_RECIPE__APP_LOAD_ADDR)
_MTB_RECIPE__APP_PC=$(shell printf "0x%x" $$(($(_MTB_RECIPE__APP_LOAD_ADDR) + 0x04)))
_MTB_RECIPE__OPENOCD_PREPARE_APP=init; reset init; load_image $(_MTB_RECIPE__OPENOCD_PROGRAM_IMG);
_MTB_RECIPE__OPENOCD_DEBUG=$(_MTB_RECIPE__OPENOCD_DEBUG_PREFIX) $(_MTB_RECIPE__OPENOCD_PREPARE_APP)
_MTB_RECIPE__OPENOCD_PROGRAM=$(_MTB_RECIPE__OPENOCD_PREPARE_APP); reg sp [mrw $(_MTB_RECIPE__APP_SP)]; reg pc [mrw $(_MTB_RECIPE__APP_PC)]; reg xPSR 0x01000000; resume; exit;
else # default case for Virgin Si
_MTB_RECIPE__OPENOCD_ERASE=init; reset init; erase_all; exit;
_MTB_RECIPE__OPENOCD_DEBUG=$(_MTB_RECIPE__OPENOCD_DEBUG_PREFIX) init; reset init;
_MTB_RECIPE__OPENOCD_PROGRAM=program $(_MTB_RECIPE__OPENOCD_PROGRAM_IMG) verify reset exit;
endif #($(BITFILE_PROVISIONED),true)

ifeq ($(APPTYPE),ram)
ifeq ($(filter erase,$(MAKECMDGOALS)),erase)
$(call mtb__error, Unable to proceed. program and erase is not supported for APPTYPE=$(APPTYPE))
endif #($(filter erase,$(MAKECMDGOALS)),erase)
endif #($(APPTYPE),ram)

ifeq ($(MTB_ERASE_EXT_MEM), 1)
_MTB_RECIPE__OPENOCD_ERASE_EXTERNAL_MEM=-s $(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH) -c "$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER)"
endif

_MTB_RECIPE__OPENOCD_ERASE_ARGS=$(_MTB_RECIPE__OPENOCD_SCRIPTS) $(_MTB_RECIPE__OPENOCD_ERASE_EXT_MEM) $(_MTB_RECIPE__OPENOCD_ERASE_EXTERNAL_MEM) -c "set DEBUG_CERTIFICATE $(CY_DBG_CERTIFICATE_PATH)" -c \
					"$(_MTB_RECIPE__OPENOCD_INTERFACE) $(_MTB_RECIPE__OPENOCD_BOARD); $(MTB_RECIPE__OPENOCD_PRETARGET_COMMAND); transport select $(_MTB_RECIPE__PROBE_INTERFACE); $(_MTB_RECIPE__OPENOCD_PROBE_SERIAL) $(_MTB_RECIPE__OPENOCD_TARGET) $(_MTB_RECIPE__OPENOCD_CUSTOM_COMMAND) $(_MTB_RECIPE__OPENOCD_ERASE)"
_MTB_RECIPE__OPENOCD_PROGRAM_ARGS=$(_MTB_RECIPE__OPENOCD_SCRIPTS) -s $(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH) -c "$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER)" -c "set DEBUG_CERTIFICATE $(CY_DBG_CERTIFICATE_PATH)" -c \
					"$(_MTB_RECIPE__OPENOCD_INTERFACE) $(_MTB_RECIPE__OPENOCD_BOARD); $(MTB_RECIPE__OPENOCD_PRETARGET_COMMAND); transport select $(_MTB_RECIPE__PROBE_INTERFACE); $(_MTB_RECIPE__OPENOCD_PROBE_SERIAL) $(_MTB_RECIPE__OPENOCD_TARGET) $(_MTB_RECIPE__OPENOCD_CUSTOM_COMMAND) $(_MTB_RECIPE__OPENOCD_PROGRAM)"
_MTB_RECIPE__OPENOCD_DEBUG_ARGS=$(_MTB_RECIPE__OPENOCD_SCRIPTS) -s $(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH) -c "$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER)" -c "set DEBUG_CERTIFICATE $(CY_DBG_CERTIFICATE_PATH)" -c \
					"$(_MTB_RECIPE__OPENOCD_INTERFACE) $(_MTB_RECIPE__OPENOCD_BOARD); $(MTB_RECIPE__OPENOCD_PRETARGET_COMMAND); transport select $(_MTB_RECIPE__PROBE_INTERFACE); $(_MTB_RECIPE__OPENOCD_PROBE_SERIAL) $(_MTB_RECIPE__OPENOCD_TARGET) $(_MTB_RECIPE__OPENOCD_CUSTOM_COMMAND) $(_MTB_RECIPE__OPENOCD_DEBUG)"

_MTB_RECIPE__JLINK_DEBUG_ARGS=-if $(_MTB_RECIPE__PROBE_INTERFACE) -device $(_MTB_RECIPE__JLINK_DEVICE_CFG) -endian little -speed auto -port 2331 -swoport 2332 -telnetport 2333 -vd -ir -localhostonly 1 -singlerun -strict -timeout 0 -nogui
