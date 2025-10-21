/*******************************************************************************
* File Name        : lv_port_indev.c
*
* Description      : This file provides implementation of low level input device
*                    driver for LVGL.
*
* Related Document : See README.md
*
******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "lv_port_indev.h"
#include "cy_utils.h"
/*#if defined(MTB_CTP_GT911)
#include "mtb_ctp_gt911.h"
#elif defined(MTB_CTP_ILI2511)
#include "mtb_ctp_ili2511.h"
#endif*/
#include "cybsp.h"


/*****************************************************************************
* Macros
*****************************************************************************/
#if defined(MTB_CTP_ILI2511)
    #define CTP_RESET_PORT       GPIO_PRT17
    #define CTP_RESET_PIN        (3U)
    #define CTP_IRQ_PORT         GPIO_PRT17
    #define CTP_IRQ_PIN          (2U)
#endif


/*******************************************************************************
* Global Variables
*******************************************************************************/
lv_indev_t *indev_touchpad;

#if defined(MTB_CTP_ILI2511)
/* ILI2511 touch controller configuration */
mtb_ctp_ili2511_config_t ctp_ili2511_cfg =
{
    .scb_inst            = CYBSP_I2C_CONTROLLER_0_HW,
    .i2c_context         = &disp_touch_i2c_controller_context,
    .rst_port            = CTP_RESET_PORT,
    .rst_pin             = CTP_RESET_PIN,
    .irq_port            = CTP_IRQ_PORT,
    .irq_pin             = CTP_IRQ_PIN,
    .irq_num             = ioss_interrupts_gpio_17_IRQn,
    .touch_event         = false,
};
#endif


/*******************************************************************************
* Function Name: touchpad_init
********************************************************************************
* Summary:
*  Initialization function for touchpad supported by LittelvGL.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void touchpad_init(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

#if defined(MTB_CTP_GT911)
    result = mtb_gt911_init(CYBSP_I2C_CONTROLLER_0_HW,
                            &disp_touch_i2c_controller_context);

#elif defined(MTB_CTP_ILI2511)
    result = mtb_ctp_ili2511_init(&ctp_ili2511_cfg);
#endif

    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }
}


/*******************************************************************************
* Function Name: touchpad_read
********************************************************************************
* Summary:
*  Touchpad read function called by the LVGL library.
*  Here you will find example implementation of input devices supported by
*  LittelvGL:
*   - Touchpad
*   - Mouse (with cursor support)
*   - Keypad (supports GUI usage only with key)
*   - Encoder (supports GUI usage only with: left, right, push)
*   - Button (external buttons to press points on the screen)
*
*   The `..._read()` function are only examples.
*   You should shape them according to your hardware.
*
*
* Parameters:
*  *indev_drv: Pointer to the input driver structure to be registered by HAL.
*  *data: Pointer to the data buffer holding touch coordinates.
*
* Return:
*  void
*
*******************************************************************************/
static void touchpad_read(lv_indev_t *indev_drv, lv_indev_data_t *data)
{
    static int touch_x = 0;
    static int touch_y = 0;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    data->state = LV_INDEV_STATE_REL;

#if defined(MTB_CTP_GT911)
    result = mtb_gt911_get_single_touch(CYBSP_I2C_CONTROLLER_0_HW,
                                        &disp_touch_i2c_controller_context, &touch_x, &touch_y);
#elif defined(MTB_CTP_ILI2511)
    result = mtb_ctp_ili2511_get_single_touch(&touch_x, &touch_y);
#endif



    if (CY_RSLT_SUCCESS == result)
    {
        data->state = LV_INDEV_STATE_PR;
    }

    /* Set the last pressed coordinates */
    data->point.x = touch_x;
    data->point.y = touch_y;
}


/*******************************************************************************
* Function Name: lv_port_indev_init
********************************************************************************
* Summary:
*  Initialization function for input devices supported by LittelvGL.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void lv_port_indev_init(void)
{
    /* Initialize your touchpad if you have. */
    touchpad_init();

    /* Register a touchpad input device */
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchpad_read);
}


/* [] END OF FILE */
