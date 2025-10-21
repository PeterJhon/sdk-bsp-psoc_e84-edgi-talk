#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define ADC_CTRL                  GET_PIN(8, 4)
#define LED_PIN_B                 GET_PIN(16, 5)
#define ADC_DEV_NAME              "adc1"
#define ADC_DEV_CHANNEL           0

rt_adc_device_t adc_dev;
rt_uint32_t value, mv, v, mv_frac;

int main(void)
{
    rt_kprintf("Hello RT-Thread\r\n");
    rt_kprintf("This core is cortex-m33\n");
    rt_pin_mode(LED_PIN_B, PIN_MODE_OUTPUT);
    rt_pin_mode(ADC_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(ADC_CTRL, PIN_HIGH);

    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);

    while (1)
    {
        rt_pin_write(LED_PIN_B, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN_B, PIN_LOW);
        rt_thread_mdelay(500);

        value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        mv = (value * 4200 + 900) / 1800;
        v = mv / 1000;
        mv_frac = mv % 1000;

        rt_kprintf("Value is: %d.%03d V\n", v, mv_frac);
    }
    return 0;
}

//Mos管控制
#define ES8388_CTRL                 GET_PIN(16, 2)  //ES8388 电源 Enable引脚
#define SPEAKER_OE_CTRL             GET_PIN(21, 6)  //功放 Enable引脚
#define WIFI_OE_CTRL                GET_PIN(16, 3)  //WIFI Enable引脚
#define WIFI_WL_REG_OE_CTRL         GET_PIN(11, 6)  //WiFi寄存器开关
#define CTRL                        GET_PIN(7, 2)   //底板 3V3 DCDC电源控制
int en_gpio(void)
{
    rt_pin_mode(WIFI_OE_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(WIFI_OE_CTRL, PIN_HIGH);

    rt_pin_mode(WIFI_WL_REG_OE_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(WIFI_WL_REG_OE_CTRL, PIN_HIGH);

    rt_pin_mode(ES8388_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(ES8388_CTRL, PIN_HIGH);

    rt_pin_mode(SPEAKER_OE_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(SPEAKER_OE_CTRL, PIN_HIGH);

    return 0;
}
INIT_BOARD_EXPORT(en_gpio);