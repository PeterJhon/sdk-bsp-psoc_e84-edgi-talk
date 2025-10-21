#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define LED_PIN_G               GET_PIN(16, 6)

int main(void)
{
    rt_kprintf("Hello RT-Thread\r\n");
    rt_kprintf("It's cortex-m55\r\n");
    rt_pin_mode(LED_PIN_G, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN_G, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN_G, PIN_HIGH);
        rt_thread_mdelay(500);
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
