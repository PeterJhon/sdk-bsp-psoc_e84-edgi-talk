################################################################################
# \file recipe_ide.mk
#
# \brief
# This make file defines the IDE export variables and target.
#
################################################################################
# \copyright
# (c) 2022-2025, Cypress Semiconductor Corporation (an Infineon company) or
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

MTB_RECIPE__IDE_SUPPORTED:=eclipse vscode uvision5 ewarm8

include $(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/recipe_ide_common.mk

# Path to debug certificatee
ifneq ($(CY_DBG_CERTIFICATE_PATH),)
CY_DBG_CERTIFICATE_PATH_APPLICATION:=$(CY_DBG_CERTIFICATE_PATH)
else
CY_DBG_CERTIFICATE_PATH:=./packets/debug_token.bin
CY_DBG_CERTIFICATE_PATH_APPLICATION:=./packets/debug_token.bin
ifneq (,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
CY_DBG_CERTIFICATE_PATH:=../packets/debug_token.bin
endif
endif

##############################################
# Eclipse VSCode
##############################################
_MTB_RECIPE__IDE_TEXT_DATA_FILE=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/recipe_ide_text_data.txt
_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE:=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/recipe_ide_template_meta_data.txt
_MTB_RECIPE__VSCODE_TEMPLATE_REGEX_DATA_FILE:=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/recipe_vscode_template_regex_data.txt
_MTB_RECIPE__IDE_TEMPLATE_DIR:=$(MTB_TOOLS__RECIPE_DIR)/make/scripts/interface_version_3

_MTB_RECIPE__IDE_TEMPLATE_SUBDIR:=$(_MTB_RECIPE__APPTYPE_DIR)/$(_MTB_RECIPE__BITFILE_LIFECYCLE_SUBDIR)/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)

ifeq ($(firstword $(MTB_APPLICATION_SUBPROJECTS)),$(_MTB_RECIPE__IDE_PRJ_DIR_NAME))
_MTB_RECIPE__IS_FIRST_PRJ=1
endif
ifeq ($(lastword $(MTB_APPLICATION_SUBPROJECTS)),$(_MTB_RECIPE__IDE_PRJ_DIR_NAME))
_MTB_RECIPE__IS_LAST_PRJ=1
endif

CY_QSPI_FLM_DIR_OUTPUT?=$(CY_QSPI_FLM_DIR)
ifeq ($(CY_QSPI_FLM_DIR_OUTPUT),)
_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER=
_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_WITH_FLAG=
else
_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER=set QSPI_FLASHLOADER $(patsubst %/,%,$(CY_QSPI_FLM_DIR_OUTPUT))/PSE84_SMIF.FLM
_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_APPLICATION=set QSPI_FLASHLOADER $(patsubst ../%/,%,$(CY_QSPI_FLM_DIR_OUTPUT))/PSE84_SMIF.FLM
_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_WITH_FLAG=-c &quot;$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER)&quot;&\#13;&\#10;
_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_APPLICATION_WITH_FLAG=-c &quot;$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_APPLICATION)&quot;&\#13;&\#10;
endif

ifneq ($(PROG_FILE),)
ifeq (,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
_MTB_RECIPE__VSCODE_HEX_FILE:=$(PROG_FILE)
_MTB_RECIPE__ECLIPSE_PROG_FILE:=$(PROG_FILE)
endif
endif

##############################################
# Common Eclipse/VSCode targets
##############################################

recipe_text_replacement_data_file:
	$(call mtb__file_write,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__JLINK_CFG&&=$(_MTB_RECIPE__JLINK_DEVICE_CFG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__JLINK_CM0_CFG&&=$(_MTB_RECIPE__JLINK_DEVICE_CM0_CFG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&PC_SYMBOL&&=$(PC_SYMBOL))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&SP_SYMBOL&&=$(SP_SYMBOL))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__FIRST_APP_NAME&&=$(firstword $(MTB_APPLICATION_SUBPROJECTS)))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__SECOND_APP_NAME&&=$(lastword $(MTB_APPLICATION_SUBPROJECTS)))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__TARGET_PROCESSOR_NAME&&=$(MTB_RECIPE__CORE))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__DEVICE_DEBUG&&=$(_MTB_RECIPE__JLINK_DEVICE_CFG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__OPENOCD_CM0_CFG&&=$(_MTB_RECIPE__OPENOCD_DEVICE_CM0_CFG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROCESSOR_COUNT&&=2)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PREBUILT_SECURE_APP&&=$(MTB_TOOLS__TARGET_DIR)/COMPONENT_CM33/TOOLCHAIN_$(TOOLCHAIN)/COMPONENT_PREBUILT_SECURE_APP/$(_MTB_RECIPE__PREBUILT_SECURE_APP))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PREBUILT_SECURE_APP_APPLICATION&&=$(patsubst $(call mtb__path_normalize,$(MTB_TOOLS__PRJ_DIR)/../)/%,%,$(call mtb__path_normalize,$(MTB_TOOLS__TARGET_DIR)/COMPONENT_CM33/TOOLCHAIN_$(TOOLCHAIN)//COMPONENT_PREBUILT_SECURE_APP/$(_MTB_RECIPE__PREBUILT_SECURE_APP))))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PREBUILT_CM0_IMAGE&&=$(MTB_TOOLS__TARGET_DIR)/COMPONENT_CM33/TOOLCHAIN_$(TOOLCHAIN)/COMPONENT_PREBUILT_CM0P/$(_MTB_RECIPE__PREBUILT_CM0_IMAGE))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PREBUILT_CM0_IMAGE_APPLICATION&&=$(patsubst $(call mtb__path_normalize,$(MTB_TOOLS__PRJ_DIR)/../)/%,%,$(call mtb__path_normalize,$(MTB_TOOLS__TARGET_DIR)/COMPONENT_CM33/TOOLCHAIN_$(TOOLCHAIN)/COMPONENT_PREBUILT_CM0P/$(_MTB_RECIPE__PREBUILT_CM0_IMAGE))))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__HEX_FILE&&=$(_MTB_RECIPE__VSCODE_HEX_FILE))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__DBG_CERTIFICATE_PATH&&=$(CY_DBG_CERTIFICATE_PATH))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__DBG_CERTIFICATE_APPLICATION_PATH&&=$(CY_DBG_CERTIFICATE_PATH_APPLICATION))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__OPENOCD_RESET_TARGET&&=$(_MTB_RECIPE__OPENOCD_RESET_TARGET))
ifeq ($(MTB_RECIPE__CORE),CM33)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__TARGET_PROCESSOR_NUMBER&&=0)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__TARGET_PROCESSOR_NAME_LOWERCASE&&=cm33)
else
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__TARGET_PROCESSOR_NUMBER&&=1)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__TARGET_PROCESSOR_NAME_LOWERCASE&&=cm55)
endif

##############################################
# Eclipse
##############################################

eclipse_generate: recipe_text_replacement_data_file recipe_eclipse_text_replacement_data_file recipe_eclipse_meta_replacement_data_file
eclipse_generate: MTB_CORE__EXPORT_CMDLINE += -textdata $(_MTB_RECIPE__IDE_TEXT_DATA_FILE) -metadata $(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE)

recipe_eclipse_text_replacement_data_file:
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_CFG_PATH&&=$(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH_WITH_FLAG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_CFG_PATH_APPLICATION&&=$(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH_APPLICATION_WITH_FLAG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_FLASHLOADER&&=$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_WITH_FLAG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_FLASHLOADER_APPLICATION&&=$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_APPLICATION_WITH_FLAG))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_APP_NAME&&=$(_MTB_RECIPE__ECLIPSE_APPLICATION_NAME))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_PRJ_NAME&&=$(_MTB_RECIPE__ECLIPSE_PROJECT_NAME))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__OPENOCD_BOARD&&=$(if $(_MTB_RECIPE__OPENOCD_BOARD),-c &quot;$(_MTB_RECIPE__OPENOCD_BOARD)&quot;&#13;&#10;,))
ifeq ($(MTB_RECIPE__CORE),CM33)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROG_FILE_CM33&&=$(subst $(MTB_RECIPE__SUFFIX_TARGET),hex,$(_MTB_RECIPE__ECLIPSE_SYM_FILE)))
else
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROG_FILE_CM55&&=$(subst $(MTB_RECIPE__SUFFIX_TARGET),hex,$(_MTB_RECIPE__ECLIPSE_SYM_FILE)))
endif
ifneq ($(filter NON_SECURE,$(VCORE_ATTRS)),)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__ADD_SYMBOL_FILE_CMD&&=add-symbol-file $(_MTB_RECIPE__ECLIPSE_SYM_FILE))
endif

recipe_eclipse_meta_replacement_data_file_default:
ifneq (,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
ifeq (,$(_MTB_RECIPE__IS_FIRST_PRJ))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=../.mtbLaunchConfigs=../.mtbLaunchConfigs)
endif
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/eclipse/$(MTB_RECIPE__CORE)/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/multi=.mtbLaunchConfigs/)
endif
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/eclipse/$(MTB_RECIPE__CORE)/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/any=.mtbLaunchConfigs)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/Proj/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)/any=.mtbLaunchConfigs)

recipe_eclipse_meta_replacement_data_file:
	$(call mtb__file_write,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),UUID=&&PROJECT_UUID&&)
ifneq (,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),APPLICATION_UUID=&&APPLICATION_UUID&&)
ifneq (,$(_MTB_RECIPE__IS_FIRST_PRJ))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/eclipse/Application/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)=../.mtbLaunchConfigs)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/App/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)/internal=../.mtbLaunchConfigs)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/App/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)/external=../.mtbLaunchConfigs)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),UPDATE_APPLICATION_PREF_FILE=1)
endif #(,$(_MTB_RECIPE__IS_FIRST_PRJ))
else #(,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/Proj/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)/single/external=.mtbLaunchConfigs)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/Proj/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)/single/internal=.mtbLaunchConfigs)
endif #(,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))

##############################################
# VSCode
##############################################

vscode_generate: recipe_text_replacement_data_file recipe_vscode_text_replacement_data_file recipe_vscode_meta_replacement_data_file recipe_vscode_regex_replacement_data_file
vscode_generate: MTB_CORE__EXPORT_CMDLINE += -textdata $(_MTB_RECIPE__IDE_TEXT_DATA_FILE) -metadata $(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE) -textregexdata $(_MTB_RECIPE__VSCODE_TEMPLATE_REGEX_DATA_FILE)

recipe_vscode_text_replacement_data_file:
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_CFG_PATH&&=$(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_CFG_PATH_APPLICATION&&=$(_MTB_RECIPE__OPENOCD_QSPI_CFG_PATH_APPLICATION))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_FLASHLOADER&&=$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__QSPI_FLASHLOADER_APPLICATION&&=$(_MTB_RECIPE__OPENOCD_QSPI_FLASHLOADER_APPLICATION))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_PRJ_NAME&&=$(APPNAME))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__OPENOCD_BOARD&&=$(_MTB_RECIPE__OPENOCD_BOARD))
ifeq ($(MTB_RECIPE__CORE),CM33)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROG_FILE_CM33&&=$(subst $(MTB_RECIPE__SUFFIX_TARGET),hex,$(_MTB_RECIPE__VSCODE_ELF_FILE)))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROG_FILE_CM33_APPLICATION&&=$(subst $(MTB_RECIPE__SUFFIX_TARGET),hex,$(_MTB_RECIPE__VSCODE_ELF_FILE_APPLICATION)))
else
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROG_FILE_CM55&&=$(subst $(MTB_RECIPE__SUFFIX_TARGET),hex,$(_MTB_RECIPE__VSCODE_ELF_FILE)))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__PROG_FILE_CM55_APPLICATION&&=$(subst $(MTB_RECIPE__SUFFIX_TARGET),hex,$(_MTB_RECIPE__VSCODE_ELF_FILE_APPLICATION)))
endif
ifneq ($(filter NON_SECURE,$(VCORE_ATTRS)),)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEXT_DATA_FILE),&&_MTB_RECIPE__ADD_SYMBOL_FILE_CMD&&=add-symbol-file $(_MTB_RECIPE__VSCODE_ELF_FILE_APPLICATION))
endif

recipe_vscode_regex_replacement_data_file:
ifeq ($(MTB_RECIPE__CORE),CM33)
	$(call mtb__file_write,$(_MTB_RECIPE__VSCODE_TEMPLATE_REGEX_DATA_FILE),^(.*)//CM33 Only//(.*)$$=\1\2)
	$(call mtb__file_append,$(_MTB_RECIPE__VSCODE_TEMPLATE_REGEX_DATA_FILE),^.*//CM55 Only//.*$$=)
else
	$(call mtb__file_write,$(_MTB_RECIPE__VSCODE_TEMPLATE_REGEX_DATA_FILE),^(.*)//CM55 Only//(.*)$$=\1\2)
	$(call mtb__file_append,$(_MTB_RECIPE__VSCODE_TEMPLATE_REGEX_DATA_FILE),^.*//CM33 Only//.*$$=)
endif

recipe_vscode_meta_replacement_data_file:
ifneq (,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
	$(call mtb__file_write,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_CORE__IDE_TEMPLATE_DIR)/vscode/dependencies_tasks.json=.vscode/tasks.json)
ifeq ($(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES),)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/CMx/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/launch_multicore.json=.vscode/launch.json)
endif
ifneq (,$(_MTB_RECIPE__IS_FIRST_PRJ))
ifeq ($(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR),KitProg3)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/Application/openocd.tcl=../openocd.tcl)
endif
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/Application/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/launch.json=../.vscode/launch.json)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__CORE_DIR)/make/scripts/interface_version_3/vscode/tasks.json=../.vscode/tasks.json)
else
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=../.vscode=../.vscode)
endif
else #(,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
	$(call mtb__file_write,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/CMx/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/launch.json=.vscode/launch.json)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__CORE_DIR)/make/scripts/interface_version_3/vscode/tasks.json=.vscode/tasks.json)
endif #(,$(_MTB_RECIPE__IS_MULTI_CORE_APPLICATION))
ifeq ($(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR),KitProg3)
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/CMx/openocd.tcl=openocd.tcl)
endif
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_TEMPLATE_META_DATA_FILE),MERGE_LAUNCH_JSON=.vscode/launch.json=.vscode/launch.json)

.PHONY: recipe_text_replacement_data_file recipe_vscode_text_replacement_data_file recipe_vscode_meta_replacement_data_file recipe_vscode_regex_replacement_data_file

##############################################
# EW UV
##############################################
_MTB_RECIPE__IDE_BUILD_DATA_FILE:=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/recipe_ide_build_data.txt

ewarm8 uvision5: MTB_CORE__EXPORT_CMDLINE += -build_data $(_MTB_RECIPE__IDE_BUILD_DATA_FILE)
ewarm8 uvision5: recipe_ide_build_data_file

recipe_ide_build_data_file:
	$(call mtb__file_write,$(_MTB_RECIPE__IDE_BUILD_DATA_FILE),LINKER_SCRIPT=$(MTB_RECIPE__LINKER_SCRIPT))

.PHONY: recipe_ide_build_data_file

##############################################
# UV
##############################################
_MTB_RECIPE__CMSIS_ARCH_NAME:=CAT1D_DFP
_MTB_RECIPE__CMSIS_VENDOR_NAME:=Infineon
_MTB_RECIPE__CMSIS_VENDOR_ID:=7

ifeq ($(MTB_RECIPE__CORE),CM55)
_MTB_RECIPE__CMSIS_PNAME:=Cortex-M55
else ifeq ($(MTB_RECIPE__CORE),CM33)
_MTB_RECIPE__CMSIS_PNAME:=Cortex-M33
endif

_MTB_RECIPE__IDE_DFP_DATA_FILE:=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/recipe_ide_dfp_data.txt

uvision5: recipe_uvision5_dfp_data_file
uvision5: MTB_CORE__EXPORT_CMDLINE += -dfp_data $(_MTB_RECIPE__IDE_DFP_DATA_FILE)

recipe_uvision5_dfp_data_file:
	$(call mtb__file_write,$(_MTB_RECIPE__IDE_DFP_DATA_FILE),DEVICE=$(DEVICE))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_DFP_DATA_FILE),DFP_NAME=$(_MTB_RECIPE__CMSIS_ARCH_NAME))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_DFP_DATA_FILE),VENDOR_NAME=$(_MTB_RECIPE__CMSIS_VENDOR_NAME))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_DFP_DATA_FILE),VENDOR_ID=$(_MTB_RECIPE__CMSIS_VENDOR_ID))
	$(call mtb__file_append,$(_MTB_RECIPE__IDE_DFP_DATA_FILE),PNAME=$(_MTB_RECIPE__CMSIS_PNAME))

uvision5: recipe_uvision5_dfp_data_file

##############################################
# EW
##############################################
ifeq ($(MTB_RECIPE__CORE),CM55)
_MTB_RECIPE__IAR_CORE_SUFFIX:=M55
endif
ifeq ($(MTB_RECIPE__CORE),CM33)
_MTB_RECIPE__IAR_CORE_SUFFIX:=M33
endif

##############################################
# Combiner/Signer Integration
##############################################
ifeq ($(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES),)
eclipse_generate: recipe_eclipse_meta_replacement_data_file_default
endif

ifneq ($(COMBINE_SIGN_JSON),)
_MTB_RECIPE__IDE_PRJ_DIR_NAME:=$(notdir $(realpath $(MTB_TOOLS__PRJ_DIR)))

_MTB_RECIPE__VSCODE_COMBINE_SIGN_MEATA_DATA_FILE=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/vscode_combine_sign_meta_data.txt

vscode_generate: MTB_CORE__EXPORT_CMDLINE += -metadata $(_MTB_RECIPE__VSCODE_COMBINE_SIGN_MEATA_DATA_FILE)
vscode_generate: recipe_vscode_combine_sign_meta

recipe_vscode_combine_sign_meta:
	$(call mtb__file_write,$(_MTB_RECIPE__VSCODE_COMBINE_SIGN_MEATA_DATA_FILE))
ifneq ($(wildcard $(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/CMx/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/launch_combine_sign.json),)
	$(call mtb__file_append,$(_MTB_RECIPE__VSCODE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/vscode/CMx/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/launch_combine_sign.json=.vscode/launch_&&IDX&&.json)
	$(call mtb__file_append,$(_MTB_RECIPE__VSCODE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPEAT=.vscode/launch_&&IDX&&.json=$(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES))
	$(call mtb__file_append,$(_MTB_RECIPE__VSCODE_COMBINE_SIGN_MEATA_DATA_FILE),MERGE_LAUNCH_JSON=.vscode/launch.json=$(foreach index,$(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES),.vscode/launch_$(index).json))
endif

_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE=$(MTB_TOOLS__OUTPUT_CONFIG_DIR)/eclipse_combine_sign_meta_data.txt

eclipse_generate: MTB_CORE__EXPORT_CMDLINE += -metadata $(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE)
eclipse_generate: recipe_eclipse_combine_sign_meta

recipe_eclipse_combine_sign_meta:
	$(call mtb__file_write,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE))
ifneq ($(wildcard $(_MTB_RECIPE__IDE_TEMPLATE_DIR)/eclipse/$(MTB_RECIPE__CORE)/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/combine_sign/Debug.launch),)
	$(call mtb__file_append,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/eclipse/$(MTB_RECIPE__CORE)/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/combine_sign/Debug.launch=.mtbLaunchConfigs/&&MTB_COMBINE_SIGN_&&IDX&&_CONFIG_NAME&& Debug $(_MTB_RECIPE__PROGRAM_INTERFACE_LAUNCH_SUFFIX).launch)
	$(call mtb__file_append,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPLACE=$(_MTB_RECIPE__IDE_TEMPLATE_DIR)/eclipse/$(MTB_RECIPE__CORE)/$(_MTB_RECIPE__IDE_TEMPLATE_SUBDIR)/combine_sign/Attach.launch=.mtbLaunchConfigs/&&MTB_COMBINE_SIGN_&&IDX&&_CONFIG_NAME&& Attach $(_MTB_RECIPE__PROGRAM_INTERFACE_LAUNCH_SUFFIX).launch)
	$(call mtb__file_append,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPLACE=$(MTB_TOOLS__RECIPE_DIR)/make/recipe/interface_version_3/Proj/$(_MTB_RECIPE__PROGRAM_INTERFACE_SUBDIR)/combine_sign/Program.launch=.mtbLaunchConfigs/&&MTB_COMBINE_SIGN_&&IDX&&_CONFIG_NAME&& Program $(_MTB_RECIPE__PROGRAM_INTERFACE_LAUNCH_SUFFIX).launch)
	$(call mtb__file_append,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPEAT=.mtbLaunchConfigs/&&MTB_COMBINE_SIGN_&&IDX&&_CONFIG_NAME&& Debug $(_MTB_RECIPE__PROGRAM_INTERFACE_LAUNCH_SUFFIX).launch=$(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES))
	$(call mtb__file_append,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPEAT=.mtbLaunchConfigs/&&MTB_COMBINE_SIGN_&&IDX&&_CONFIG_NAME&& Attach $(_MTB_RECIPE__PROGRAM_INTERFACE_LAUNCH_SUFFIX).launch=$(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES))
	$(call mtb__file_append,$(_MTB_RECIPE__ECLIPSE_COMBINE_SIGN_MEATA_DATA_FILE),TEMPLATE_REPEAT=.mtbLaunchConfigs/&&MTB_COMBINE_SIGN_&&IDX&&_CONFIG_NAME&& Program $(_MTB_RECIPE__PROGRAM_INTERFACE_LAUNCH_SUFFIX).launch=$(MTB_COMBINE_SIGN_$(_MTB_RECIPE__IDE_PRJ_DIR_NAME)_HEX_FILES))
endif

endif
