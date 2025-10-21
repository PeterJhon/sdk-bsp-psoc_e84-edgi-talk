/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     Rbb666       first version
 * 2025-08-20     Hydevcode
 */

#include "board.h"
#define ES8388_CTRL             GET_PIN(16, 2)
#define SPEAKER_OE_CTRL         GET_PIN(21, 6)
#define WIFI_OE_CTRL            GET_PIN(16, 3)
#define WIFI_WL_REG_OE_CTRL     GET_PIN(11, 6)
#define CTRL                    GET_PIN(7, 2)

void cy_bsp_all_init(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    Cy_SysClk_ClkHfSetSource(0, CY_SYSCLK_CLKHF_IN_CLKPATH3);
    Cy_SysClk_ClkHfSetDivider(0, CY_SYSCLK_CLKHF_DIVIDE_BY_16);
}

void _start(void)
{
    extern int entry(void);
    entry();
    while (1);
    __builtin_unreachable();
}

void poweroff(void)
{
    rt_pin_mode(WIFI_OE_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(WIFI_OE_CTRL, PIN_LOW);

    rt_pin_mode(WIFI_WL_REG_OE_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(WIFI_WL_REG_OE_CTRL, PIN_LOW);

    rt_pin_mode(ES8388_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(ES8388_CTRL, PIN_LOW);

    rt_pin_mode(SPEAKER_OE_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(SPEAKER_OE_CTRL, PIN_LOW);

    rt_pin_mode(CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(CTRL, PIN_LOW);

    Cy_SysClk_PllDisable(SRSS_DPLL_LP_0_PATH_NUM);
    Cy_SysPm_SystemEnterHibernate();
}

#ifdef RT_USING_MSH
    MSH_CMD_EXPORT(poweroff, The software enables the system to shut down. Simply press the button to restart it.);
#endif
