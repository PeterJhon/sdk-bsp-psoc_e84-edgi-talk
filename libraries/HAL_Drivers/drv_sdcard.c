/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-05     vandoul      first
 */

#include <rtthread.h>
#include "cybsp.h"
#include "cy_sysint.h"
#include "cy_sd_host.h"
#include "mtb_hal_sdhc.h"

#ifdef BSP_USING_SDCARD
#define SDHC_IRQ_PRIORITY                   (3U)
#define LOG_TAG "drv.sdio"
#include <drv_log.h>
#include <dfs_fs.h>
#include <rtdevice.h>

static mtb_hal_sdhc_t sdhc_obj;
static cy_stc_sd_host_context_t sdhc_host_context;
struct rthw_sdio
{
    struct rt_device parent;
    struct dfs_partition part;
    struct rt_device_blk_geometry geometry;
};
static rt_err_t rt_mmcsd_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_mmcsd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_mmcsd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_mmcsd_control(rt_device_t dev, int cmd, void *args)
{
    struct rthw_sdio *sdio = (struct rthw_sdio *)dev;
    struct dfs_partition *part = &sdio->part;
    struct rt_device_blk_geometry *geometry = &sdio->geometry;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        rt_memcpy(args, geometry, sizeof(struct rt_device_blk_geometry));
        break;
    case RT_DEVICE_CTRL_BLK_PARTITION:
        rt_memcpy(args, part, sizeof(struct dfs_partition));
    default:
        break;
    }
    return RT_EOK;
}

static rt_ssize_t rt_mmcsd_read(rt_device_t dev,
                                rt_off_t    pos,
                                void       *buffer,
                                rt_size_t   size)
{
    rt_err_t err = 0;
    struct rthw_sdio *sdio = (struct rthw_sdio *)dev;
    off_t offset = sdio->part.offset;

    LOG_D("mmc read: off:%d pos:%d size:%d", offset, pos, size);
    if (dev == RT_NULL)
    {
        rt_set_errno(-RT_EINVAL);
        return 0;
    }

    rt_sem_take(sdio->part.lock, RT_WAITING_FOREVER);
    do
    {
        size_t block_count =  size;
        uint32_t addr = (offset + pos);
        cy_rslt_t result = mtb_hal_sdhc_read_async(&sdhc_obj, addr, buffer, &block_count);
        if (CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
        result = mtb_hal_sdhc_wait_transfer_complete(&sdhc_obj);
        if (CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
    }
    while (0);
    rt_sem_release(sdio->part.lock);

    /* the length of reading must align to SECTOR SIZE */
    if (err)
    {
        rt_set_errno(-RT_EIO);
        return 0;
    }
    return size;
}

static rt_ssize_t rt_mmcsd_write(rt_device_t dev,
                                 rt_off_t    pos,
                                 const void *buffer,
                                 rt_size_t   size)
{
    rt_err_t err = 0;
    struct rthw_sdio *sdio = (struct rthw_sdio *)dev;
    off_t offset = sdio->part.offset;

    LOG_D("mmc write: off:%d pos:%d size:%d", offset, pos, size);
    if (dev == RT_NULL)
    {
        rt_set_errno(-RT_EINVAL);
        return 0;
    }

    rt_sem_take(sdio->part.lock, RT_WAITING_FOREVER);
    do
    {
        size_t block_count =  size ;
        uint32_t addr = (offset + pos);
        cy_rslt_t result = mtb_hal_sdhc_write_async(&sdhc_obj, addr, buffer, &block_count);
        if (CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
        result = mtb_hal_sdhc_wait_transfer_complete(&sdhc_obj);
        if (CY_RSLT_SUCCESS != result)
        {
            err = -RT_ERROR;
            break;
        }
    }
    while (0);
    rt_sem_release(sdio->part.lock);

    /* the length of reading must align to SECTOR SIZE */
    if (err)
    {
        rt_set_errno(-RT_EIO);
        return 0;
    }
    return size;
}
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops mmcsd_blk_ops =
{
    rt_mmcsd_init,
    rt_mmcsd_open,
    rt_mmcsd_close,
    rt_mmcsd_read,
    rt_mmcsd_write,
    rt_mmcsd_control
};
#endif

bool Cy_SD_Host_IsCardConnected(SDHC_Type const *base)
{
    (void) base;
    return true;
}

static void sd_card_isr(void)
{
    mtb_hal_sdhc_process_interrupt(&sdhc_obj);
}

int rt_hw_sdio_init(void)
{
    struct rthw_sdio *sdio = RT_NULL;
    cy_rslt_t hal_status;
    cy_en_sd_host_status_t pdl_sdhc_status;
    cy_en_sysint_status_t pdl_sysint_status;

    sdio = rt_malloc(sizeof(struct rthw_sdio));
    if (sdio == RT_NULL)
    {
        LOG_E("malloc rthw_sdio fail");
        return RT_NULL;
    }
    rt_memset(sdio, 0, sizeof(struct rthw_sdio));
    /* register mmcsd device */
    sdio->parent.type  = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    sdio->parent.ops  = &mmcsd_blk_ops;
#else
    sdio->parent.init = rt_mmcsd_init;
    sdio->parent.open = rt_mmcsd_open;
    sdio->parent.close = rt_mmcsd_close;
    sdio->parent.read = rt_mmcsd_read;
    sdio->parent.write = rt_mmcsd_write;
    sdio->parent.control = rt_mmcsd_control;
#endif

    do
    {
        /* Configuration structure for the SDHC interrupt. */
        cy_stc_sysint_t sdhc_isr_config =
        {
            .intrSrc = CYBSP_SDHC_1_IRQ,
            .intrPriority = SDHC_IRQ_PRIORITY,
        };

        Cy_SD_Host_Enable(CYBSP_SDHC_1_HW);

        pdl_sdhc_status = Cy_SD_Host_Init(CYBSP_SDHC_1_HW, &CYBSP_SDHC_1_config, &sdhc_host_context);
        if (CY_SD_HOST_SUCCESS != pdl_sdhc_status)
        {
            rt_kprintf("Cy_SD_Host_Init returns error status\n\r");
        }

        pdl_sdhc_status = Cy_SD_Host_InitCard(CYBSP_SDHC_1_HW, &CYBSP_SDHC_1_card_cfg, &sdhc_host_context);
        if (CY_SD_HOST_SUCCESS != pdl_sdhc_status)
        {
            rt_kprintf("Cy_SD_Host_InitCard returns error status\n\r");
        }

        hal_status = mtb_hal_sdhc_setup(&sdhc_obj, &CYBSP_SDHC_1_sdhc_hal_config, NULL, &sdhc_host_context);

        if (CY_RSLT_SUCCESS != hal_status)
        {
            rt_kprintf("mtb_hal_sdhc_setup returns error status\n\r");
        }

        pdl_sysint_status = Cy_SysInt_Init(&sdhc_isr_config, sd_card_isr);

        if (CY_SYSINT_SUCCESS != pdl_sysint_status)
        {
            rt_kprintf("Cy_SysInt_Init returns error status\n\r");
        }

        NVIC_EnableIRQ((IRQn_Type)sdhc_isr_config.intrSrc);

        rt_uint32_t block_count;
        cy_rslt_t rslt = mtb_hal_sdhc_get_block_count(&sdhc_obj, &block_count);
        if (rslt != CY_RSLT_SUCCESS)
        {
            LOG_E("get block count fail: (0x%x)", rslt);
            break;
        }
        LOG_D("block count:%d(0x%x)", block_count, block_count);

        sdio->geometry.bytes_per_sector = 512;
        sdio->geometry.block_size = 512;
        sdio->geometry.sector_count = block_count;

        sdio->part.lock = rt_sem_create("sem_sd0", 1, RT_IPC_FLAG_FIFO);
        if (sdio->part.lock == RT_NULL)
        {
            LOG_E("create part.lock fail");
            break;
        }

        rt_uint8_t *sector = rt_malloc(512);
        if (sector == RT_NULL)
        {
            LOG_E("malloc sector fail");
            break;
        }
        if (rt_mmcsd_read(&sdio->parent, 0, sector, 1) < 0)
        {
            LOG_E("rt_mmcsd_read fail");
            rt_free(sector);
            break;
        }
        rslt = dfs_filesystem_get_partition(&sdio->part, sector, 0);
        rt_free(sector);
        if (rslt != RT_EOK)
        {
            LOG_E("partition not found!");
            break;
        }

        rslt = rt_device_register(&(sdio->parent), "sd0",
                                  RT_DEVICE_FLAG_RDWR);

        if (rslt != RT_EOK)
        {
            LOG_E("register device fail!");
            break;
        }

        return RT_EOK;

    }
    while (0);

    if (sdio)
    {
        if (sdio->part.lock)
        {
            rt_sem_delete(sdio->part.lock);
        }
        rt_free(sdio);
    }

    return -RT_ERROR;
}
INIT_DEVICE_EXPORT(rt_hw_sdio_init);

#endif

