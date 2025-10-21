#include "cy_pdl.h"
#include "cybsp.h"
#include "security_config.h"

#define Enable_HyperRam 1U

#if (1U == Enable_HyperRam)

#include "retarget_io_init.h"
#include "mtb_hal.h"
#include "cycfg_qspi_memslot.h"
#include "mtb_serial_memory.h"

static mtb_serial_memory_t    serial_memory_obj;
static cy_stc_smif_context_t  smif_context;
static mtb_hal_gpio_t p8_7_obj;

#define CACHE_ENABLE                    (0U)
#define ADDRESS_SIZE_IN_BYTES           (4U)
#define NUM_BYTES_PER_LINE              (16U)
#define SMIF_INIT_TIMEOUT_USEC          (10000U)
#define SMIF_1_PSRAM_ADDRESS            (0x64000000U)

static void check_status(char *message, uint32_t status)
{
    if (status)
    {
        printf("\n\r====================================================\n\r");
        printf("\n\rFAIL: %s\n\r", message);
        printf("Error Code: 0x%x\n\r", (int) status);
        printf("\n\r====================================================\n\r");
        while (true);
    }
}

static void smif_ospi_psram_init(void)
{
    cy_rslt_t result;

    /* Disable SMIF Block for reconfiguration. */
    Cy_SMIF_Disable(CYBSP_SMIF_CORE_1_PSRAM_HW);

    /* Initialize SMIF-1 Peripheral. */
    result = Cy_SMIF_Init((CYBSP_SMIF_CORE_1_PSRAM_hal_config.base),
                          (CYBSP_SMIF_CORE_1_PSRAM_hal_config.config),
                          SMIF_INIT_TIMEOUT_USEC, &smif_context);

    check_status("Cy_SMIF_Init failed", result);

    /* Configure Data Select Option for SMIF-1 */
    Cy_SMIF_SetDataSelect(CYBSP_SMIF_CORE_1_PSRAM_hal_config.base,
                          smif1BlockConfig.memConfig[0]->slaveSelect,
                          smif1BlockConfig.memConfig[0]->dataSelect);

    /* Enable the SMIF_CORE_1 block. */
    Cy_SMIF_Enable(CYBSP_SMIF_CORE_1_PSRAM_hal_config.base, &smif_context);

    /* Set-up serial memory for SMIF_CORE_1. */
    result = mtb_serial_memory_setup(&serial_memory_obj,
                                     MTB_SERIAL_MEMORY_CHIP_SELECT_2,
                                     CYBSP_SMIF_CORE_1_PSRAM_HW,
                                     &CYBSP_SMIF_CORE_1_PSRAM_hal_clock,
                                     &smif_context, &smif1BlockConfig);

    check_status("serial memory setup failed", result);
}
#endif


int main(void)
{
    uint32_t ns_stack;
    funcptr_void NonSecure_ResetHandler;
    cy_rslt_t result;

    if (CY_SYSLIB_RESET_HIB_WAKEUP ==
            (Cy_SysLib_GetResetReason() & CY_SYSLIB_RESET_HIB_WAKEUP))
    {
        Cy_SysPm_IoUnfreeze();
    }

    /* TrustZone setup */
    TZ_SAU_Setup();

#if defined (__FPU_USED) && (__FPU_USED == 1U) && \
      defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)
    /*FPU initialization*/
    initFPU();
#endif

    /* Set up internal routing, pins, and clock-to-peripheral connections */
    result = cybsp_init();

    /* Board initialization failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }
    /* Enable global interrupts */
    __enable_irq();

    Cy_SysPm_SetHibernateWakeupSource((uint32_t)CY_SYSPM_HIBERNATE_PIN0_HIGH | (uint32_t)CY_SYSPM_HIBERNATE_PIN1_LOW);
    /*Enables the PD1 Power Domain*/
    Cy_System_EnablePD1();

    /*
    * Initialize the clock for the APP_MMIO_TCM (512K) peripheral group.
    * This sets up the necessary clock and peripheral routing to ensure
    * the APP_MMIO_TCM can be correctly accessed and utilized.
    */
    Cy_SysClk_PeriGroupSlaveInit(
        CY_MMIO_CM55_TCM_512K_PERI_NR,
        CY_MMIO_CM55_TCM_512K_GROUP_NR,
        CY_MMIO_CM55_TCM_512K_SLAVE_NR,
        CY_MMIO_CM55_TCM_512K_CLK_HF_NR
    );

    /*
    * Initialize the clock for the SMIF0 peripheral group.
    * This sets up the necessary clock and peripheral routing to ensure
    * the SMIF0 can be correctly accessed and utilized.
    */
    Cy_SysClk_PeriGroupSlaveInit(
        CY_MMIO_SMIF0_PERI_NR,
        CY_MMIO_SMIF0_GROUP_NR,
        CY_MMIO_SMIF0_SLAVE_NR,
        CY_MMIO_SMIF0_CLK_HF_NR
    );

    /* Enable SOCMEM */
    Cy_SysEnableSOCMEM(true);

    /* Configure semaphore */
    config_sema();

    /* Configure MPC for NS */
    config_mpc();

    ns_stack = (uint32_t)(*((uint32_t*)CM33_NS_SP_STORE));
    __TZ_set_MSP_NS(ns_stack);

    NonSecure_ResetHandler = (funcptr_void)(*((uint32_t*)CM33_NS_RESET_HANDLER_STORE));

    /* Clear SYSCPU and APPCPU power domain dependency set by boot code */
    cy_pd_pdcm_clear_dependency(CY_PD_PDCM_APPCPU, CY_PD_PDCM_SYSCPU);

#if (1U == Enable_HyperRam)
    mtb_hal_gpio_setup(&p8_7_obj, 8, 7);
    mtb_hal_gpio_configure(&p8_7_obj, MTB_HAL_GPIO_DIR_OUTPUT, MTB_HAL_GPIO_DRIVE_STRONG);
    mtb_hal_gpio_write(&p8_7_obj, 1);

    init_retarget_io();

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "PSOC Edge MCU: CM33 Secure Mode"
           "****************** \r\n");
#if (1U == CACHE_ENABLE)
    /* Cache attributes set to Write Back, Read & Write Allocate, to demonstrate
     * cache clean and invalidation operations. */
    cy_stc_smif_cache_region_t cache_region_0 =
    {
        .enabled = true,
        .start_address = SMIF_1_PSRAM_ADDRESS,
        .end_address = SMIF_1_PSRAM_ADDRESS + CY_XIP_PORT1_SIZE,
        .cache_attributes = CY_SMIF_CACHEABLE_WB_RWA
    };

    cy_stc_smif_cache_config_t cache_config =
    {
        .enabled = true,
        .cache_retention_on = true,
    };

    memcpy(&cache_config .cache_region_0, &cache_region_0, sizeof(cache_region_0));

    Cy_SMIF_InitCache(SMIF1_CACHE_BLOCK, &cache_config);

    printf("PSRAM Cache is Enabled\r\n");
#else
    printf("PSRAM Cache is Disabled\r\n");
#endif

    /* Initialize PSRAM and set-up serial memory */
    smif_ospi_psram_init();

    check_status("smif_ospi_psram_init error", (uint32_t)result);

    /* Enable XIP mode for the SMIF memory slot associated with the PSRAM. */
    result = mtb_serial_memory_enable_xip(&serial_memory_obj, true);
    check_status("mtb_serial_memory_enable_xip: failed", result);

    /* Enable write for the SMIF memory slot associated with the PSRAM. */
    result = mtb_serial_memory_set_write_enable(&serial_memory_obj, true);
    check_status("mtb_serial_memory_set_write_enable: failed", result);
    printf("PSRAM init successful \r\n");

    printf("****************** "
           "PSOC Edge MCU: CM33 Secure Mode Exit"
           "****************** \r\n\n");
#endif
    /* Configure PPC for NS */
    config_ppc();

    Cy_SysLib_Delay(100u);

    /* Start non-secure application */
    NonSecure_ResetHandler();

    for (;;)
    {
    }
}
