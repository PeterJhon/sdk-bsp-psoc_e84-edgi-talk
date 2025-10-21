/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-13     Rbb666       first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifdef BSP_USING_PWM0
#ifndef TCPWM_0_GRP_0_PWM_5_CONFIG
#define TCPWM_0_GRP_0_PWM_5_CONFIG \
    {                               \
        .name = "pwm0",             \
        .channel = CYBSP_TCPWM_0_GRP_0_PWM_5_NUM,               \
        .tcpwm_pwm_config =&CYBSP_TCPWM_0_GRP_0_PWM_5_config,     \
        .base =CYBSP_TCPWM_0_GRP_0_PWM_5_HW,                \
        .hal_pwm_configurator=&CYBSP_TCPWM_0_GRP_0_PWM_5_hal_config, \
    }
#endif /* TCPWM_0_GRP_0_PWM_5_CONFIG */
#endif /* BSP_USING_PWM0 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PWM_CONFIG_H__ */
