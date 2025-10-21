/*-----------------------------------------------------------------------------------*/
/* Common definitions for the device                                                 */
/*-----------------------------------------------------------------------------------*/

ITCM_NS_START                    = 0x00000000;
ITCM_S_START                     = 0x10000000;
ITCM_SIZE                        = 0x00040000;

DTCM_NS_START                    = 0x20000000;
DTCM_S_START                     = 0x30000000;
DTCM_SIZE                        = 0x00040000;

RRAM_NVM_MAIN_NS_START           = 0x22000000;
RRAM_NVM_MAIN_S_START            = 0x32000000;
RRAM_NVM_MAIN_NS_CBUS_START      = 0x02000000;
RRAM_NVM_MAIN_S_CBUS_START       = 0x12000000;
RRAM_NVM_MAIN_SIZE               = 0x00040000;

RRAM_NVM_SECURE_NS_START         = 0x23C00000;
RRAM_NVM_SECURE_S_START          = 0x33C00000;
RRAM_NVM_SECURE_NS_CBUS_START    = 0x03C00000;
RRAM_NVM_SECURE_S_CBUS_START     = 0x13C00000;
RRAM_NVM_SECURE_SIZE             = 0x00040000;

SRAM0_NS_SAHB_START              = 0x24000000;
SRAM0_S_SAHB_START               = 0x34000000;
SRAM0_NS_CBUS_START              = 0x04000000;
SRAM0_S_CBUS_START               = 0x14000000;
SRAM0_SIZE                       = 0x00080000;

SRAM1_NS_SAHB_START              = 0x24080000;
SRAM1_S_SAHB_START               = 0x34080000;
SRAM1_NS_CBUS_START              = 0x04080000;
SRAM1_S_CBUS_START               = 0x14080000;
SRAM1_SIZE                       = 0x00080000;

SOCMEMSRAM_NS_SAHB_START         = 0x26000000;
SOCMEMSRAM_S_SAHB_START          = 0x36000000;
SOCMEMSRAM_NS_CBUS_START         = 0x06000000;
SOCMEMSRAM_S_CBUS_START          = 0x16000000;
SOCMEMSRAM_SIZE                  = 0x00500000;

XIP0_NS_SAHB_START               = 0x60000000;
XIP0_S_SAHB_START                = 0x70000000;
XIP0_NS_CBUS_START               = 0x08000000;
XIP0_S_CBUS_START                = 0x18000000;
XIP0_SIZE                        = 0x04000000; /* This needs to be updated with the actual size of the memory that is used for XIP0 */

XIP1_S_START                     = 0x74000000;
XIP1_NS_CBUS_START               = 0x0C000000;
XIP1_S_CBUS_START                = 0x1C000000;
XIP1_SIZE                        = 0x04000000; /* This needs to be updated with the actual size of the flash that is used for XIP1 */

HYPERRAM_NS_SAHB_START           = 0x64000000;
HYPERRAM_SIZE                    = 0x00400000; /* 4MB HyperRAM */

/*-----------------------------------------------------------------------------------*/
XIP0_SECTOR_SIZE                 = DEFINED(FLASH_SECTOR_SIZE) ? FLASH_SECTOR_SIZE : (256 *1024); /* Default Sector size set to 256KB */

CM0P_RAMVECTORS_ALIGNMENT        = 1024;
CM33_RAMVECTORS_ALIGNMENT        = 1024;
CM55_RAMVECTORS_ALIGNMENT        = 1024;

CM33S_MSP_STACK_SIZE             = 0x0000800;
CM33NS_MSP_STACK_SIZE            = 0x0000800;
CM55_MSP_STACK_SIZE              = 0x0000800;

MSP_STACK_SIZE                   = 0x00001000;
HEAP_SIZE                        = 0x0001000;
CODE_NSC_SIZE                    = 0x100;

CM33S_APP_HEADER_SIZE            = 0x00000400;
CM33NS_APP_HEADER_SIZE           = 0x00000400;
CM55NS_APP_HEADER_SIZE           = 0x00000400;

SRAM0_SHARED_SIZE                = 0x00002000;   /* 8K memory reserved for cm0 and cm33-sec IPC data */
SRAM0_SHARED_CM0_SIZE            = 0x00001000;   /* Out of 8K shared memory, 4K is reserved for CM0 */

SRAM1_SHARED_SIZE                = 0x00002000;   /* 8K memory reserved for cm33-s, cm33-ns and cm55 IPC data */
SRAM1_SHARED_CM33NS_SIZE         = 0x00000800;   /* Out of 8K shared memory, 2K is reserved for CM33-S */
SRAM1_SHARED_CM33S_SIZE          = 0x00000800;   /* Out of 8K shared memory, 2K is reserved for CM33-S */

SOCMEMSRAM_SHARED_SIZE           = 0x00100000;   /* 1M memory reserved for SHARED SOCMEM  */

XIP0_CM33S_SLOT_SIZE             = (512 * 1024); /* Slot size is set to 512 KB */
XIP0_CM33S_IMAGE_OFFSET          = 0x00100000;
XIP0_CM33S_APP_OFFSET            = XIP0_CM33S_IMAGE_OFFSET + CM33S_APP_HEADER_SIZE;
ASSERT(2*XIP0_SECTOR_SIZE <= XIP0_CM33S_SLOT_SIZE, "CM33 S Image can't fit in the slot. Increase the slot size XIP0_CM33S_SLOT_SIZE")
XIP0_CM33S_APP_SIZE              = (XIP0_CM33S_SLOT_SIZE - CM33S_APP_HEADER_SIZE - CODE_NSC_SIZE - XIP0_SECTOR_SIZE);

XIP0_CM33NS_SLOT_SIZE            = (2304 * 1024); /* Slot size is set to 2.25MB */
XIP0_CM33NS_IMAGE_OFFSET         = 0x00340000;
XIP0_CM33NS_APP_OFFSET           = XIP0_CM33NS_IMAGE_OFFSET + CM33NS_APP_HEADER_SIZE;
ASSERT(2*XIP0_SECTOR_SIZE <= XIP0_CM33NS_SLOT_SIZE, "CM33 NS Image can't fit in the slot. Increase the slot size XIP0_CM33NS_SLOT_SIZE")
XIP0_CM33NS_APP_SIZE             = (XIP0_CM33NS_SLOT_SIZE - CM33NS_APP_HEADER_SIZE - XIP0_SECTOR_SIZE);

XIP0_CM55NS_SLOT_SIZE            = (3328 * 1024); /* Slot size is set to 3.25MB */
XIP0_CM55NS_IMAGE_OFFSET         = 0x00580000;
XIP0_CM55NS_APP_OFFSET           = XIP0_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE;
ASSERT(2*XIP0_SECTOR_SIZE <= XIP0_CM55NS_SLOT_SIZE, "CM55 Image can't fit in the slot. Increase the slot size XIP0_CM55NS_SLOT_SIZE")
XIP0_CM55NS_APP_SIZE             = (XIP0_CM55NS_SLOT_SIZE - CM55NS_APP_HEADER_SIZE - XIP0_SECTOR_SIZE);


RRAM_CM33S_IMAGE_OFFSET          = DEFINED(APP_RRAM_CM33S_IMAGE_OFFSET) ? APP_RRAM_CM33S_IMAGE_OFFSET : 0x00011000;
RRAM_CM33S_APP_OFFSET            = (RRAM_CM33S_IMAGE_OFFSET + CM33S_APP_HEADER_SIZE);
RRAM_CM33S_APP_SIZE              = 0x0001AB00; /* (108KB - 0x500) */

RRAM_CM33NS_IMAGE_OFFSET         = 0x0002A000;
RRAM_CM33NS_APP_OFFSET           = RRAM_CM33NS_IMAGE_OFFSET + CM33NS_APP_HEADER_SIZE;
RRAM_CM33NS_APP_SIZE             = 0;

RRAM_CM55NS_IMAGE_OFFSET         = 0x00040800;
RRAM_CM55NS_APP_OFFSET           = RRAM_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE;
RRAM_CM55NS_APP_SIZE             = 0;

SRAM0_CM33S_IMAGE_OFFSET         = 0x00001000;
SRAM0_CM33S_APP_OFFSET           = SRAM0_CM33S_IMAGE_OFFSET;
SRAM0_CM33S_APP_SIZE             = (28*1024);

SRAM0_CM33S_DATA_OFFSET          = 0x00008000;
SRAM0_CM33S_DATA_SIZE            = (300*1024);

SRAM0_SHARED_OFFSET              = 0x00053000;

SRAM0_CM33NS_IMAGE_OFFSET        = 0x00000000;
SRAM0_CM33NS_APP_OFFSET          = SRAM0_CM33NS_IMAGE_OFFSET;
SRAM0_CM33NS_APP_SIZE            = 0x00000000;

SRAM0_CM33NS_DATA_OFFSET         = SRAM0_SHARED_OFFSET + SRAM0_SHARED_SIZE;
SRAM0_CM33NS_DATA_SIZE           = SRAM0_SIZE - (SRAM0_SHARED_SIZE + SRAM0_SHARED_OFFSET);

SRAM0_CM55NS_IMAGE_OFFSET        = 0x00000000;
SRAM0_CM55NS_APP_OFFSET          = SRAM0_CM55NS_IMAGE_OFFSET;
SRAM0_CM55NS_APP_SIZE            = 0x00000000;

SRAM1_CM55NS_DATA_OFFSET         = 0x00000000;
SRAM1_CM55NS_DATA_SIZE           = 0x00000000;

SRAM1_CM33S_IMAGE_OFFSET         = 0x00000000;
SRAM1_CM33S_APP_OFFSET           = SRAM1_CM33S_IMAGE_OFFSET;
SRAM1_CM33S_APP_SIZE             = 0x00000000;

SRAM1_CM33S_DATA_OFFSET          = 0x00000000;
SRAM1_CM33S_DATA_SIZE            = 0x00000000;

SRAM1_CM33NS_IMAGE_OFFSET        = 0x00000000;
SRAM1_CM33NS_APP_OFFSET          = SRAM1_CM33NS_IMAGE_OFFSET;
SRAM1_CM33NS_APP_SIZE            = 0x00040000 - SRAM1_CM33NS_APP_OFFSET;

SRAM1_CM55NS_IMAGE_OFFSET        = 0x00000000;
SRAM1_CM55NS_APP_OFFSET          = SRAM1_CM55NS_IMAGE_OFFSET;
SRAM1_CM55NS_APP_SIZE            = 0x00000000;

SRAM1_CM33NS_DATA_OFFSET         = 0x00040000;
SRAM1_CM33NS_DATA_SIZE           = 0x00040000 - SRAM1_SHARED_SIZE;



SRAM1_SHARED_OFFSET              = SRAM1_CM33NS_DATA_OFFSET + SRAM1_CM33NS_DATA_SIZE;

SOCMEMSRAM_CM33S_IMAGE_OFFSET    = 0x00000000;
SOCMEMSRAM_SEC_APP_OFFSET        = SOCMEMSRAM_CM33S_IMAGE_OFFSET;
SOCMEMSRAM_SEC_APP_SIZE          = 0x00000000;

/*
SOCMEMSRAM Partition
--------------------------------------------------------------------
PARTITION               OFFSET                 SIZE
--------------------------------------------------------------------
CM55NS_APP            CM55NS_IMAGE_OFFSET     APP_SIZE
GPUBUF                GPUBUF_OFFSET           GPUBUF_SIZE
SHARED_MEM            SHARED_OFFSET           SHARED_SIZE
CM55NS_DATA           CM55NS_DATA_OFFSET      DATA_SIZE
CM33NS_APP            CM33NS_APP_OFFSET       CM33NS_APP_SIZE
CM33NS_DATA           CM33NS_DATA_OFFSET      CM33NS_DATA_SIZE
*/
SOCMEMSRAM_CM55NS_IMAGE_OFFSET   = 0x00000000;
SOCMEMSRAM_CM55NS_APP_OFFSET     = SOCMEMSRAM_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE;

/* APP_SOCMEMSRAM_* can be passed from application makefile to override default size*/
SOCMEMSRAM_CM55NS_APP_SIZE_DEF   = DEFINED(APP_SOCMEMSRAM_CM55NS_APP_SIZE) ? APP_SOCMEMSRAM_CM55NS_APP_SIZE : 0x00080000 ;
SOCMEMSRAM_CM55NS_APP_SIZE       = (SOCMEMSRAM_CM55NS_APP_SIZE_DEF - (SOCMEMSRAM_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE));

SOCMEMSRAM_GPUBUF_OFFSET         = SOCMEMSRAM_CM55NS_IMAGE_OFFSET + SOCMEMSRAM_CM55NS_APP_SIZE_DEF;
SOCMEMSRAM_GPUBUF_SIZE           = DEFINED(APP_SOCMEMSRAM_GPUBUF_SIZE) ? APP_SOCMEMSRAM_GPUBUF_SIZE : 0x00080000;

SOCMEMSRAM_SHARED_OFFSET         = SOCMEMSRAM_GPUBUF_OFFSET + SOCMEMSRAM_GPUBUF_SIZE;
SOCMEMSRAM_SHARED_SIZE           = DEFINED(APP_SOCMEMSRAM_SHARED_SIZE) ? APP_SOCMEMSRAM_SHARED_SIZE : 0x00100000;

SOCMEMSRAM_CM55NS_DATA_OFFSET    = SOCMEMSRAM_SHARED_OFFSET + SOCMEMSRAM_SHARED_SIZE;
SOCMEMSRAM_CM55NS_DATA_SIZE      = DEFINED(APP_SOCMEMSRAM_CM55NS_DATA_SIZE) ? APP_SOCMEMSRAM_CM55NS_DATA_SIZE : 0x00100000;

SOCMEMSRAM_CM33NS_IMAGE_OFFSET   = SOCMEMSRAM_CM55NS_DATA_OFFSET + SOCMEMSRAM_CM55NS_DATA_SIZE;
SOCMEMSRAM_CM33NS_APP_OFFSET     = SOCMEMSRAM_CM33NS_IMAGE_OFFSET;
SOCMEMSRAM_CM33NS_APP_SIZE       = DEFINED(APP_SOCMEMSRAM_CM33NS_APP_SIZE) ? APP_SOCMEMSRAM_CM33NS_APP_SIZE : 0x00100000;

SOCMEMSRAM_CM33NS_DATA_OFFSET    = SOCMEMSRAM_CM33NS_APP_OFFSET + SOCMEMSRAM_CM33NS_APP_SIZE;
SOCMEMSRAM_CM33NS_DATA_SIZE      = DEFINED(APP_SOCMEMSRAM_CM33NS_DATA_SIZE) ? APP_SOCMEMSRAM_CM33NS_DATA_SIZE : 0x00100000;

/* Specify the output format for the linker script */
OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
/* Search for libraries in the current directory */
SEARCH_DIR(.)
/* Specify the group of libraries to link against */
GROUP(-lgcc -lc -lnosys)
/* Define the entry point of the program, which is the reset handler */
ENTRY(Reset_Handler)

/* Define the stack size for the application */
PROVIDE(__StackSize = 0x1000);

/* Include the device memory definitions generated by the Device Configurator */
CYMEM_CM33_0_m33_persist_START = 0x2202A000;
CYMEM_CM33_0_m33_persist_C_START = 0x0202A000;
CYMEM_CM33_0_m33_persist_SIZE = 0x00040000;
CYMEM_CM33_0_m33_persist_OFFSET = 0x0002A000;
CYMEM_CM33_0_m33_nvm_START = 0x60340000;
CYMEM_CM33_0_m33_nvm_C_START = 0x08340000;
CYMEM_CM33_0_m33_nvm_SIZE = 0x00240000;
CYMEM_CM33_0_m33_nvm_OFFSET = 0x00340000;
CYMEM_CM33_0_m33_m55_shared_START = 0x26180000;
CYMEM_CM33_0_m33_m55_shared_C_START = 0x06180000;
CYMEM_CM33_0_m33_m55_shared_SIZE = 0x00300000;
CYMEM_CM33_0_m33_m55_shared_OFFSET = 0x00180000;
CYMEM_CM33_0_gfx_mem_START = 0x26480000;
CYMEM_CM33_0_gfx_mem_C_START = 0x06480000;
CYMEM_CM33_0_gfx_mem_SIZE = 0x00080000;
CYMEM_CM33_0_gfx_mem_OFFSET = 0x00480000;
CYMEM_CM33_0_m33s_code_START = 0x24002000;
CYMEM_CM33_0_m33s_code_C_START = 0x04002000;
CYMEM_CM33_0_m33s_code_SIZE = 0x00007000;
CYMEM_CM33_0_m33s_code_OFFSET = 0x00002000;
CYMEM_CM33_0_m33_nsc_START = 0x24054000;
CYMEM_CM33_0_m33_nsc_C_START = 0x04054000;
CYMEM_CM33_0_m33_nsc_SIZE = 0x00001000;
CYMEM_CM33_0_m33_nsc_OFFSET = 0x00054000;
CYMEM_CM33_0_m33_code_START = 0x24055000;
CYMEM_CM33_0_m33_code_C_START = 0x04055000;
CYMEM_CM33_0_m33_code_SIZE = 0x00068000;
CYMEM_CM33_0_m33_code_OFFSET = 0x00055000;
CYMEM_CM33_0_m33_data_START = 0x240BD000;
CYMEM_CM33_0_m33_data_C_START = 0x040BD000;
CYMEM_CM33_0_m33_data_SIZE = 0x00040000;
CYMEM_CM33_0_m33_data_OFFSET = 0x000BD000;
CYMEM_CM33_0_m33_m55_system_shared_START = 0x240FD000;
CYMEM_CM33_0_m33_m55_system_shared_C_START = 0x040FD000;
CYMEM_CM33_0_m33_m55_system_shared_SIZE = 0x00003000;
CYMEM_CM33_0_m33_m55_system_shared_OFFSET = 0x000FD000;

/* Define the memory layout */
MEMORY
{
    /* Include the memory regions generated by the Device Configurator.
       This file contains the memory region definitions for the device,
       which are used to define the memory layout in this linker script. */
    m33_persist : ORIGIN = 0x2202A000, LENGTH = 0x00040000
    m33_persist_C : ORIGIN = 0x0202A000, LENGTH = 0x00040000
    m33_nvm : ORIGIN = 0x60340000, LENGTH = 0x00240000
    m33_nvm_C : ORIGIN = 0x08340000, LENGTH = 0x00240000
    m33_m55_shared : ORIGIN = 0x26180000, LENGTH = 0x00300000
    m33_m55_shared_C : ORIGIN = 0x06180000, LENGTH = 0x00300000
    gfx_mem : ORIGIN = 0x26480000, LENGTH = 0x00080000
    gfx_mem_C : ORIGIN = 0x06480000, LENGTH = 0x00080000
    m33s_code : ORIGIN = 0x24002000, LENGTH = 0x00007000
    m33s_code_C : ORIGIN = 0x04002000, LENGTH = 0x00007000
    m33_nsc : ORIGIN = 0x24054000, LENGTH = 0x00001000
    m33_nsc_C : ORIGIN = 0x04054000, LENGTH = 0x00001000
    m33_code : ORIGIN = 0x24055000, LENGTH = 0x00068000
    m33_code_C : ORIGIN = 0x04055000, LENGTH = 0x00068000
    m33_data : ORIGIN = 0x240BD000, LENGTH = 0x00040000
    m33_data_C : ORIGIN = 0x040BD000, LENGTH = 0x00040000
    m33_m55_system_shared : ORIGIN = 0x240FD000, LENGTH = 0x00003000
    m33_m55_system_shared_C : ORIGIN = 0x040FD000, LENGTH = 0x00003000
    hyperram : ORIGIN = 0x64000000, LENGTH = 0x00400000
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */

/* Device definitions */
VECTORS_ALIGNMENT = 1024;
m33_nvm_C_Offset = ORIGIN(m33_nvm_C) - ORIGIN(m33_nvm);
m33_code_C_Offset = ORIGIN(m33_code_C) - ORIGIN(m33_code);
m33_data_C_Offset = ORIGIN(m33_data_C) - ORIGIN(m33_data);

/* The size of the MCU boot header area at the start of the code region */
MCUBOOT_HEADER_SIZE = 0x400;

/* Define the sections */
SECTIONS
{
    /* This section is intended to reserve a space for MCUBoot header in LMA address space */
    .mcu_boot_header_lma(NOLOAD) : ALIGN(MCUBOOT_HEADER_SIZE)
    {
        . += MCUBOOT_HEADER_SIZE;
    } > m33_nvm

    /* This section is intended to reserve a space for MCUBoot header in VMA address space */
    .mcu_boot_header_vma(NOLOAD) : ALIGN(MCUBOOT_HEADER_SIZE)
    {
        . += MCUBOOT_HEADER_SIZE;
    } > m33_nvm_C

    /* This section is intended to hold the main non-secure (NS) application code for the Cortex-M33 */
    .app_code_main : ALIGN(VECTORS_ALIGNMENT)
    {
        /* Keep the vector table */
        KEEP(*(.vectors))
        /* Keep initializers */
        KEEP(*(.init))
        /* Keep finalizers */
        KEEP(*(.fini))
        /* Static constructors */
        *crtbegin.*(.ctors)
        *crtbegin?.*(.ctors)
        *(EXCLUDE_FILE(*crtend?.* *crtend.*) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        /* Static destructors and atexit() */
        *crtbegin.*(.dtors)
        *crtbegin?.*(.dtors)
        *(EXCLUDE_FILE(*crtend?.* *crtend.*) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        . = ALIGN(4);

        /* Array of pointers to preinint functions */
        PROVIDE_HIDDEN(__preinit_array_start = .);

        KEEP(*(.preinit_array))

        PROVIDE_HIDDEN(__preinit_array_end = .);

        . = ALIGN(4);

        /* Array of pointers to init functions */
        PROVIDE_HIDDEN(__init_array_start = .);

        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))

        PROVIDE_HIDDEN(__init_array_end = .);

        . = ALIGN(4);

        /* Array of pointers to finalizer functions */

        PROVIDE_HIDDEN(__fini_array_start = .);

        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))

        PROVIDE_HIDDEN(__fini_array_end = .);

        /* Read only code (constants) */
        *(.rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        /* Exclude certain files from this section as they will be placed in RAM */
        *(EXCLUDE_FILE(*cy_syslib.* *cy_syslib_ext.* *cy_smif.* *cy_smif_memslot.* *cy_smif_sfdp.* *cy_smif_hb_flash.* *cyhal_qspi.* *mtb_hal_memoryspi.* *mtb_serial_memory.* *cy_secure_sockets.* *WHD/COMPONENT_WIFI6/src/*.* *lwip-network-interface-integration/source/*.*
        *source/iperf_utility/*.* *source/iperf/*.* *cy_sd_host.* *mtb_hal_sdhc.* *lwip/src*.* *whd-bsp-integration/*.* *freertos/Source/*.* *clib-support/*.* *abstraction-rtos/*.* *cmsis/*.* *lwip-freertos-integration/*.* *_arm_addsubdf3.* *_arm_muldivdf3.*) .text*)

        /* section information for utest */
        . = ALIGN(4);
        __rt_utest_tc_tab_start = .;
        KEEP(*(UtestTcTab))
        __rt_utest_tc_tab_end = .;

        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);

        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;

        /* section information for initialization */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;

        /* Check for load address mismatch */
        ASSERT(
            ADDR(.app_code_main) - ORIGIN(m33_nvm_C) == LOADADDR(.app_code_main) - ORIGIN(m33_nvm),
            "There is a load address mismatch for .app_code_main. The section offset within the VMA region does not match the section offset within the LMA region."
        );
    } > m33_nvm_C AT > m33_nvm

    /* Exception tables for ARM architecture */
    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)

        /* Check for load address mismatch */
        ASSERT(
            ADDR(.ARM.extab) - ORIGIN(m33_nvm_C) == LOADADDR(.ARM.extab) - ORIGIN(m33_nvm),
            "There is a load address mismatch for .ARM.extab. The section offset within the VMA region does not match the section offset within the LMA region."
        );
    } > m33_nvm_C AT > m33_nvm

    /* Exception index tables for ARM architecture */
    .ARM.exidx : ALIGN(4)
    {
        __exidx_start = .;

        *(.ARM.exidx* .gnu.linkonce.armexidx.*)

        __exidx_end = .;

        /* Check for load address mismatch */
        ASSERT(
            ADDR(.ARM.exidx) - ORIGIN(m33_nvm_C) == LOADADDR(.ARM.exidx) - ORIGIN(m33_nvm),
            "There is a load address mismatch for .ARM.exidx. The section offset within the VMA region does not match the section offset within the LMA region."
        );
    } > m33_nvm_C AT > m33_nvm

    /* Define copying of data from flash memory to RAM during the startup */
    .copy.table : ALIGN(4)
    {
        __copy_table_start__ = .;

        /* Performance-sensitive or critical functions that must be executed in SRAM */
        LONG(LOADADDR(.cy_sram_code) + m33_nvm_C_Offset)  /* From C-Bus addr */
        LONG(ADDR(.cy_sram_code) - m33_data_C_Offset)      /* To S-Bus addr */
        LONG(SIZEOF(.cy_sram_code)/4)                       /* Size in words */

        /* An initialized data in SRAM (First slot) */
        LONG (LOADADDR(.data) + m33_nvm_C_Offset)         /* From C-Bus addr */
        LONG (ADDR(.data))                                  /* To S-Bus addr */
        LONG (SIZEOF(.data)/4)                              /* Size in words */

        /* Performance-sensitive or critical functions that need to be executed in SRAM */
        LONG(LOADADDR(.app_code_ram) + m33_nvm_C_Offset)     /* From C-Bus addr */
        LONG(ADDR(.app_code_ram) - m33_code_C_Offset)         /* To S-Bus addr */
        LONG(SIZEOF(.app_code_ram)/4)                          /* Size in words */

        __copy_table_end__ = .;

        /* Check for load address mismatch */
        ASSERT(
            ADDR(.copy.table) - ORIGIN(m33_nvm_C) == LOADADDR(.copy.table) - ORIGIN(m33_nvm),
            "There is a load address mismatch for .copy.table. The section offset within the VMA region does not match the section offset within the LMA region."
        );
    } > m33_nvm_C AT > m33_nvm

    . = ALIGN(4);
    .ctors :
    {
        PROVIDE(__ctors_start__ = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE(__ctors_end__ = .);
    } > m33_nvm_C

    . = ALIGN(4);
    .dtors :
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    } > m33_nvm_C

    /* Define zeroing of the uninitialized data section */
    .zero.table : ALIGN(4)
    {
        __zero_table_start__ = .;

        LONG(__bss_start__)                       /* Start of the zero-initialized data section */
        LONG((__bss_end__ - __bss_start__)/4)     /* Size of the zero-initialized data section in words */

        __zero_table_end__ = .;

        /* Check for load address mismatch */
        ASSERT(
            ADDR(.zero.table) - ORIGIN(m33_nvm_C) == LOADADDR(.zero.table) - ORIGIN(m33_nvm),
            "There is a load address mismatch for .zero.table. The section offset within the VMA region does not match the section offset within the LMA region."
        );
    } > m33_nvm_C AT > m33_nvm

    /* A section for performance-sensitive or critical functions that need to be executed in SRAM */
    .app_code_ram : ALIGN(4)
    {
        KEEP(*(.cy_sram1_code))
        KEEP(*(.cy_ramfunc))
        KEEP(*(.text.cy_os_common))
        *cy_syslib_ext.*(.text*)
        *cy_syslib.*(.text*)
        *cy_smif.*(.text*)
        *cy_smif_memslot.*(.text*)
        *cy_smif_sfdp.*(.text*)
        *cy_smif_hb_flash.*(.text*)
        *cyhal_qspi.*(.text*)
        *mtb_hal_memoryspi.*(.text*)
        *mtb_serial_memory.*(.text*)
        *cy_secure_sockets.*(.text*)
        *WHD/COMPONENT_WIFI6/src/*.*(.text*)
        *lwip-network-interface-integration/source/*.*(.text*)
        *source/iperf_utility/*.*(.text*)
        *source/iperf/*.*(.text*)
        *cy_sd_host.*(.text*)
        *mtb_hal_sdhc.*(.text*)
        *lwip/src*.*(.text*)
        *whd-bsp-integration/*.*(.text*)
        *freertos/Source/*.*(.text*)
        *clib-support/*.*(.text*)
        *abstraction-rtos/*.*(.text*)
        *cmsis/*.*(.text*)
        *lwip-freertos-integration/*.*(.text*)
        *_arm_addsubdf3.*(.text*)
        *_arm_muldivdf3.*(.text*)

        . = ALIGN(4);
    } > m33_code_C AT > m33_nvm


    /* A section for the vector table */
    .ram_vectors (NOLOAD) : ALIGN(VECTORS_ALIGNMENT)
    {
        KEEP(*(.ram_vectors))
    } > m33_data

    /* A section for performance-sensitive or critical functions that must be executed in SRAM */
    .cy_sram_code : ALIGN(4)
    {
        KEEP(*(.cy_sram_code))
        KEEP(*(.text.cy_os_common))

        . = ALIGN(4);
    } > m33_data_C AT > m33_nvm

    /* A section for initialized data memory */
    .data : ALIGN(4)
    {
        __data_start__ = .;

        /* Data memory */
        *(.data*)
        KEEP(*(.jcr*))

        . = ALIGN(4);

        __data_end__ = .;
    } > m33_data AT > m33_nvm

    /* A section for non-initialized data memory */
    .bss(NOLOAD) : ALIGN(4)
    {
        __bss_start__ = .;

        *(.bss*)
        *(COMMON)

        . = ALIGN(4);

        __bss_end__ = .;
    } > m33_data

    /* A section for variables that should not be initialized during the device startup */
    .noinit (NOLOAD) :
    {
        KEEP(*(.noinit))
    } > m33_data

    /* A section for the heap memory */
    .heap(NOLOAD) : ALIGN(8)
    {
        __HeapBase = .;
        __end__ = .;
        end = __end__;

        KEEP(*(.heap*))

        . = ORIGIN(m33_data) + LENGTH(m33_data) - __StackSize;
        __HeapLimit = .;
    } > m33_data

    /* Define stack top, and stack limit */
    __StackTop = ORIGIN(m33_data) + LENGTH(m33_data);
    __StackLimit = __StackTop - __StackSize;
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(
        __StackLimit >= __HeapLimit,
        "Error: m33_data region overflowed with stack. Ensure that the stack size is within the available RAM."
    )

    /* A section for shared RAM memory */
    .cy_sharedmem(NOLOAD) : ALIGN(4)
    {
        KEEP(*(.cy_sharedmem))

        . = ALIGN(4);
    } > m33_m55_system_shared

    /* A section for shared SOC memory */
    .cy_shared_socmem (NOLOAD) : ALIGN(4)
    {
        KEEP(*(.cy_shared_socmem))

        . = ALIGN(4);
    } > m33_m55_shared


    /* A section for the GPU buffer */
    .cy_gpu_buf(NOLOAD) :
    {
        KEEP(*(.cy_gpu_buf))
    }  > gfx_mem

    /* A section for HyperRAM memory */
    .cy_hyperram(NOLOAD) : ALIGN(4)
    {
        KEEP(*(.cy_hyperram))

        . = ALIGN(4);
    } > hyperram
}