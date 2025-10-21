/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author         Notes
 * 2022-07-25   Rbb666         first version
 */

#include "board.h"
#include <rtdevice.h>

#ifdef BSP_USING_RTC

//#define DRV_DEBUG
#define LOG_TAG                         "drv.rtc"
#include <drv_log.h>

static rt_rtc_dev_t ifx32_rtc_dev;

static int get_day_of_week(int day, int month, int year)
{
    int ret;
    int k = 0;
    int j = 0;

    if (month < CY_RTC_MARCH)
    {
        month += CY_RTC_MONTHS_PER_YEAR;
        year--;
    }

    k = (year % 100);
    j = (year / 100);
    ret = (day + (13 * (month + 1) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    ret = ((ret + 6) % 7);

    return ret;
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    struct tm tm = {0};
    cy_stc_rtc_config_t new_time = {0};

    gmtime_r(&time_stamp, &tm);

    if (tm.tm_year < 100)
    {
        return -RT_ERROR;
    }

    new_time.sec     = tm.tm_sec;
    new_time.min     = tm.tm_min;
    new_time.hour    = tm.tm_hour;
    new_time.date    = tm.tm_mday;
    new_time.month   = tm.tm_mon;
    new_time.year    = tm.tm_year - 100;
    new_time.dayOfWeek    = get_day_of_week(tm.tm_mday, tm.tm_mon, tm.tm_year);

    Cy_RTC_SetDateAndTime(&new_time);

    LOG_D("set rtc time.");

    return RT_EOK;
}

static rt_err_t ifx_rtc_get_timeval(struct timeval *tv)
{
    struct tm tm_new = {0};
    cy_stc_rtc_config_t date_time = {0};

    Cy_RTC_GetDateAndTime(&date_time);

    tm_new.tm_sec  = date_time.sec;
    tm_new.tm_min  = date_time.min;
    tm_new.tm_hour = date_time.hour;
    tm_new.tm_mday = date_time.date;
    tm_new.tm_mon  = date_time.month;
    tm_new.tm_year = date_time.year + 100;

    tv->tv_sec = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{

    /* Variable used to store return status of RTC API */
    cy_en_rtc_status_t rtc_status;
    uint32_t rtc_access_retry = 500;

    /* RTC block doesn't allow to access, when synchronizing the user registers
    * and the internal actual RTC registers. It will return RTC_BUSY value, if
    * it is not available to update the configuration values. Needs to retry,
    * if it doesn't return CY_RTC_SUCCESS. */

    do
    {
        rtc_status = Cy_RTC_Init(&CYBSP_RTC_config);
        rtc_access_retry--;
        rt_thread_mdelay(5);
    }
    while ((rtc_status != CY_RTC_SUCCESS) && (rtc_access_retry != 0));

    return rtc_status;
}

static rt_err_t _rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    ifx_rtc_get_timeval(&tv);
    *(time_t *)sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}

static rt_err_t _rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;

    if (set_rtc_time_stamp(*sec))
    {
        result = -RT_ERROR;
    }

    LOG_D("RTC: set rtc_time %d", *sec);

    return result;
}

static const struct rt_rtc_ops _rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    RT_NULL,
    RT_NULL,
    ifx_rtc_get_timeval,
    RT_NULL,
};

/**
 * @brief    RTC initialization function.
 *
 * @return   RT_EOK indicates successful initialization, other value indicates failed;
 */
static int rt_hw_rtc_init(void)
{
    rt_err_t result = RT_EOK;

    ifx32_rtc_dev.ops = &_rtc_ops;

    if (rt_hw_rtc_register(&ifx32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL) != RT_EOK)
    {
        LOG_E("rtc init failed");
        result = -RT_ERROR;
    }
    else
    {
        LOG_D("rtc init success");
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif
