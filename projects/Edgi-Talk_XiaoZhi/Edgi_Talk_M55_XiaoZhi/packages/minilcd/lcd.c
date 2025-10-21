#include "lcd.h"
#include "lcd_init.h"
#include "lcdfont.h"


void LCD_Fill(rt_uint16_t xsta, rt_uint16_t ysta, rt_uint16_t xend, rt_uint16_t yend, rt_uint16_t color)
{
    rt_uint16_t i, j;
    LCD_Address_Set(xsta, ysta, xend - 1, yend - 1);
    for (i = ysta; i < yend; i++)
    {
        for (j = xsta; j < xend; j++)
        {
            LCD_WR_DATA(color);
        }
    }
}

void LCD_DrawPoint(rt_uint16_t x, rt_uint16_t y, rt_uint16_t color)
{
    LCD_Address_Set(x, y, x, y);
    LCD_WR_DATA(color);
}

void LCD_DrawLine(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2, rt_uint16_t color)
{
    rt_uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)incx = 1;
    else if (delta_x == 0)incx = 0;
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0;
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x;
    else distance = delta_y;
    for (t = 0; t < distance + 1; t++)
    {
        LCD_DrawPoint(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}


void LCD_DrawRectangle(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2, rt_uint16_t color)
{
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}


void Draw_Circle(rt_uint16_t x0, rt_uint16_t y0, rt_uint8_t r, rt_uint16_t color)
{
    int a, b;
    a = 0;
    b = r;
    while (a <= b)
    {
        LCD_DrawPoint(x0 - b, y0 - a, color);       //3
        LCD_DrawPoint(x0 + b, y0 - a, color);       //0
        LCD_DrawPoint(x0 - a, y0 + b, color);       //1
        LCD_DrawPoint(x0 - a, y0 - b, color);       //2
        LCD_DrawPoint(x0 + b, y0 + a, color);       //4
        LCD_DrawPoint(x0 + a, y0 - b, color);       //5
        LCD_DrawPoint(x0 + a, y0 + b, color);       //6
        LCD_DrawPoint(x0 - b, y0 + a, color);       //7
        a++;
        if ((a * a + b * b) > (r * r))
        {
            b--;
        }
    }
}


void LCD_ShowChinese(rt_uint16_t x, rt_uint16_t y, rt_uint8_t *s, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    while (*s != 0)
    {
        if (sizey == 12) LCD_ShowChinese12x12(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 16) LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 24) LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 32) LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
        else return;
        s += 2;
        x += sizey;
    }
}


void LCD_ShowChinese12x12(rt_uint16_t x, rt_uint16_t y, rt_uint8_t *s, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    rt_uint8_t i, j, m = 0;
    rt_uint16_t k;
    rt_uint16_t HZnum;
    rt_uint16_t TypefaceNum;
    rt_uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;

    HZnum = sizeof(tfont12) / sizeof(typFNT_GB12);
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont12[k].Index[0] == *(s)) && (tfont12[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont12[k].Msk[i] & (0x01 << j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (tfont12[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc);
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;
    }
}


void LCD_ShowChinese16x16(rt_uint16_t x, rt_uint16_t y, rt_uint8_t *s, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    rt_uint8_t i, j, m = 0;
    rt_uint16_t k;
    rt_uint16_t HZnum;
    rt_uint16_t TypefaceNum;
    rt_uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont16) / sizeof(typFNT_GB16);
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont16[k].Msk[i] & (0x01 << j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (tfont16[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc);
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;
    }
}


void LCD_ShowChinese24x24(rt_uint16_t x, rt_uint16_t y, rt_uint8_t *s, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    rt_uint8_t i, j, m = 0;
    rt_uint16_t k;
    rt_uint16_t HZnum;
    rt_uint16_t TypefaceNum;
    rt_uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont24) / sizeof(typFNT_GB24);
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont24[k].Msk[i] & (0x01 << j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (tfont24[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc); //��һ����
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;
    }
}

void LCD_ShowChinese32x32(rt_uint16_t x, rt_uint16_t y, rt_uint8_t *s, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    rt_uint8_t i, j, m = 0;
    rt_uint16_t k;
    rt_uint16_t HZnum;
    rt_uint16_t TypefaceNum;
    rt_uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont32) / sizeof(typFNT_GB32);
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont32[k].Msk[i] & (0x01 << j))LCD_WR_DATA(fc);
                        else LCD_WR_DATA(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (tfont32[k].Msk[i] & (0x01 << j)) LCD_DrawPoint(x, y, fc); //��һ����
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue;
    }
}


void LCD_ShowChar(rt_uint16_t x, rt_uint16_t y, rt_uint8_t num, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    rt_uint8_t temp, sizex, t, m = 0;
    rt_uint16_t i, TypefaceNum;
    rt_uint16_t x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    num = num - ' ';
    LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1);
    for (i = 0; i < TypefaceNum; i++)
    {
        if (sizey == 12)temp = ascii_1206[num][i];
        else if (sizey == 16)temp = ascii_1608[num][i];
        else if (sizey == 24)temp = ascii_2412[num][i];
        else if (sizey == 32)temp = ascii_3216[num][i];
        else return;
        for (t = 0; t < 8; t++)
        {
            if (!mode)
            {
                if (temp & (0x01 << t))LCD_WR_DATA(fc);
                else LCD_WR_DATA(bc);
                m++;
                if (m % sizex == 0)
                {
                    m = 0;
                    break;
                }
            }
            else
            {
                if (temp & (0x01 << t))LCD_DrawPoint(x, y, fc);
                x++;
                if ((x - x0) == sizex)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}


void LCD_ShowString(rt_uint16_t x, rt_uint16_t y, const rt_uint8_t *p, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey, rt_uint8_t mode)
{
    while (*p != '\0')
    {
        LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
        x += sizey / 2;
        p++;
    }
}


rt_uint32_t mypow(rt_uint8_t m, rt_uint8_t n)
{
    rt_uint32_t result = 1;
    while (n--)result *= m;
    return result;
}


void LCD_ShowIntNum(rt_uint16_t x, rt_uint16_t y, rt_uint16_t num, rt_uint8_t len, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey)
{
    rt_uint8_t t, temp;
    rt_uint8_t enshow = 0;
    rt_uint8_t sizex = sizey / 2;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
                continue;
            }
            else enshow = 1;

        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}


void LCD_ShowFloatNum1(rt_uint16_t x, rt_uint16_t y, float num, rt_uint8_t len, rt_uint16_t fc, rt_uint16_t bc, rt_uint8_t sizey)
{
    rt_uint8_t t, temp, sizex;
    rt_uint16_t num1;
    sizex = sizey / 2;
    num1 = num * 100;
    for (t = 0; t < len; t++)
    {
        temp = (num1 / mypow(10, len - t - 1)) % 10;
        if (t == (len - 2))
        {
            LCD_ShowChar(x + (len - 2)*sizex, y, '.', fc, bc, sizey, 0);
            t++;
            len += 1;
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}

void LCD_ShowPicture(rt_uint16_t x, rt_uint16_t y, rt_uint16_t length, rt_uint16_t width, const rt_uint8_t pic[])
{
    rt_uint16_t i, j;
    rt_uint32_t k = 0;
    LCD_Address_Set(x, y, x + length - 1, y + width - 1);
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            LCD_WR_DATA8(pic[k * 2]);
            LCD_WR_DATA8(pic[k * 2 + 1]);
            k++;
        }
    }
}


