#include "lcd.h"
#include "font.h"

uint16_t POINT_COLOR = 0x0000;
uint16_t BACK_COLOR = 0xFFFF;

_lcd_dev lcddev = {0};

void LCD_WR_Reg(uint16_t c)
{
    int i;
    LCD_A0_CLR;
    LCD_CS_CLR;
    for (i = 0; i < 8; i++)
    {
        if (c & 0x80)
        {
            LCD_SDA_SET;
        }
        else
            LCD_SDA_CLR;
        LCD_SCL_CLR;
        LCD_SCL_SET;
        c <<= 1;
    }
    LCD_CS_SET;
}

void LCD_WriteData(uint16_t dat)
{
    int i;
    LCD_A0_SET;
    LCD_CS_CLR;
    for (i = 0; i < 8; i++)
    {
        if (dat & 0x80)
        {
            LCD_SDA_SET;
        }
        else
            LCD_SDA_CLR;
        LCD_SCL_CLR;
        LCD_SCL_SET;
        dat <<= 1;
    }
    LCD_CS_SET;
}

void LCD_Write_Data(uint16_t dat16)
{
    LCD_WriteData(dat16 >> 8);
    LCD_WriteData(dat16);
}

void Address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    //  xq=0;yq=0;
    LCD_WR_Reg(0X2A);
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0XFF);
    LCD_WriteData(x2 >> 8);
    LCD_WriteData(x2 & 0XFF);

    LCD_WR_Reg(0X2B);
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0XFF);
    LCD_WriteData(y2 >> 8);
    LCD_WriteData(y2 & 0XFF);
    LCD_WR_Reg(0X2C);
}

void LCD_Init(void)
{
    LCD_RES_SET;
    HAL_Delay(1); // Delay 1ms
    LCD_RES_CLR;
    HAL_Delay(1); // Delay 1ms
    LCD_RES_SET;
    HAL_Delay(120); // Delay 120ms
    LCD_CS_CLR;
    //************* Start Initial Sequence **********//
    LCD_WR_Reg(0xCF);
    LCD_WriteData(0x00);
    LCD_WriteData(0xD9);
    LCD_WriteData(0X30);

    LCD_WR_Reg(0xED);
    LCD_WriteData(0x64);
    LCD_WriteData(0x03);
    LCD_WriteData(0X12);
    LCD_WriteData(0X81);

    LCD_WR_Reg(0xE8);
    LCD_WriteData(0x85);
    LCD_WriteData(0x10);
    LCD_WriteData(0x78);

    LCD_WR_Reg(0xCB);
    LCD_WriteData(0x39);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x34);
    LCD_WriteData(0x02);

    LCD_WR_Reg(0xF7);
    LCD_WriteData(0x20);

    LCD_WR_Reg(0xEA);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WR_Reg(0xC0);    // Power control
    LCD_WriteData(0x21); // VRH[5:0]

    LCD_WR_Reg(0xC1);    // Power control
    LCD_WriteData(0x12); // SAP[2:0];BT[3:0]

    LCD_WR_Reg(0xC5); // VCM control
    LCD_WriteData(0x32);
    LCD_WriteData(0x3C);

    LCD_WR_Reg(0xC7); // VCM control2
    LCD_WriteData(0XC1);

    LCD_WR_Reg(0x36); // Memory Access Control
    LCD_WriteData(0x08);
    // LCD_WriteData(0x68);

    LCD_WR_Reg(0x3A);
    LCD_WriteData(0x55);

    LCD_WR_Reg(0xB1);
    LCD_WriteData(0x00);
    LCD_WriteData(0x18);

    LCD_WR_Reg(0xB6); // Display Function Control
    LCD_WriteData(0x0A);
    LCD_WriteData(0xA2);

    LCD_WR_Reg(0xF2); // 3Gamma Function Disable
    LCD_WriteData(0x00);

    LCD_WR_Reg(0x26); // Gamma curve selected
    LCD_WriteData(0x01);

    // LCD_WR_Reg(0xE0); // Set Gamma
    // LCD_WriteData(0x0F);
    // LCD_WriteData(0x20);
    // LCD_WriteData(0x1E);
    // LCD_WriteData(0x09);
    // LCD_WriteData(0x12);
    // LCD_WriteData(0x0B);
    // LCD_WriteData(0x50);
    // LCD_WriteData(0XBA);
    // LCD_WriteData(0x44);
    // LCD_WriteData(0x09);
    // LCD_WriteData(0x14);
    // LCD_WriteData(0x05);
    // LCD_WriteData(0x23);
    // LCD_WriteData(0x21);
    // LCD_WriteData(0x00);

    // LCD_WR_Reg(0XE1); // Set Gamma
    // LCD_WriteData(0x00);
    // LCD_WriteData(0x19);
    // LCD_WriteData(0x19);
    // LCD_WriteData(0x00);
    // LCD_WriteData(0x12);
    // LCD_WriteData(0x07);
    // LCD_WriteData(0x2D);
    // LCD_WriteData(0x28);
    // LCD_WriteData(0x3F);
    // LCD_WriteData(0x02);
    // LCD_WriteData(0x0A);
    // LCD_WriteData(0x08);
    // LCD_WriteData(0x25);
    // LCD_WriteData(0x2D);
    // LCD_WriteData(0x0F);

    LCD_WR_Reg(0x11); // Exit Sleep
    HAL_Delay(120);
    LCD_WR_Reg(0x29); // Display on

    LCD_LED_ON;

    lcddev.width = 240;
    lcddev.height = 320;
}

void GUI_Clear(uint16_t color)
{
    uint16_t i;
    uint16_t j;
    Address_set(0, 0, 319, 239);
    for (i = 0; i < 240; i++)
    {
        for (j = 0; j < 320; j++)
        {
            LCD_Write_Data(color);
        }
    }
}

void LCD_WR_REG(uint16_t regval)
{
    int i;
    LCD_A0_CLR;
    LCD_CS_CLR;
    for (i = 0; i < 8; i++)
    {
        if (regval & 0x80)
        {
            LCD_SDA_SET;
        }
        else
            LCD_SDA_CLR;
        LCD_SCL_CLR;
        LCD_SCL_SET;
        regval <<= 1;
    }
    LCD_CS_SET;
}

void LCD_WR_DATA(uint16_t data)
{
    int i;
    LCD_A0_SET;
    LCD_CS_CLR;
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            LCD_SDA_SET;
        }
        else
            LCD_SDA_CLR;
        LCD_SCL_CLR;
        LCD_SCL_SET;
        data <<= 1;
    }
    LCD_CS_SET;
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

void LCD_DisplayOn(void)
{
    LCD_WR_REG(0X29);
}

void LCD_DisplayOff(void)
{
    LCD_WR_REG(0X28);
}

void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    Address_set(x, y, x, y);
    LCD_Write_Data(color);
}

void LCD_Fast_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Write_Data(color);
}

void LCD_Clear(uint16_t color)
{
    uint16_t i;
    uint8_t j;
    Address_set(0, 0, 239, 319);
    for (i = 0; i < 320; i++)
    {
        for (j = 0; j < 240; j++)
        {
            LCD_Write_Data(color);
        }
    }
}

void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    uint16_t ylen = 0;

    xlen = ex - sx + 1;
    ylen = ey - sy + 1;

    Address_set(sx, sy, ex, ey);
    for (i = 0; i < xlen; i++)
    {
        for (j = 0; j < ylen; j++)
        {
            LCD_Write_Data(color);
        }
    }
}

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
        incx = 1;
    else if (delta_x == 0)
        incx = 0;
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0;
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x;
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++)
    {
        LCD_DrawPoint(uRow, uCol, POINT_COLOR);
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

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_DrawLine(x1, y1, x2, y1);
    LCD_DrawLine(x1, y1, x1, y2);
    LCD_DrawLine(x1, y2, x2, y2);
    LCD_DrawLine(x2, y1, x2, y2);
}

void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);
    while (a <= b)
    {
        LCD_DrawPoint(x0 + a, y0 - b, POINT_COLOR); // 5
        LCD_DrawPoint(x0 + b, y0 - a, POINT_COLOR); // 0
        LCD_DrawPoint(x0 + b, y0 + a, POINT_COLOR); // 4
        LCD_DrawPoint(x0 + a, y0 + b, POINT_COLOR); // 6
        LCD_DrawPoint(x0 - a, y0 + b, POINT_COLOR); // 1
        LCD_DrawPoint(x0 - b, y0 + a, POINT_COLOR);
        LCD_DrawPoint(x0 - a, y0 - b, POINT_COLOR); // 2
        LCD_DrawPoint(x0 - b, y0 - a, POINT_COLOR); // 7
        a++;

        if (di < 0)
            di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
    num = num - ' ';

    //	Address_set(x,y,x+size-1,y+size-1);
    for (t = 0; t < csize; t++)
    {
        if (size == 12)
            temp = asc2_1206[num][t];
        else if (size == 16)
            temp = asc2_1608[num][t];
        else if (size == 24)
            temp = asc2_2412[num][t];
        else
            return;
        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
                LCD_DrawPoint(x, y, POINT_COLOR);
            else if (mode == 0)
                LCD_DrawPoint(x, y, BACK_COLOR);
            temp <<= 1;
            y++;
            if (y >= 320)
                return;
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                if (x >= 240)
                    return;
                break;
            }
        }
    }
}

uint32_t LCD_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0);
                continue;
            }
            else
                enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0);
    }
}

void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                if (mode & 0X80)
                    LCD_ShowChar(x + (size / 2) * t, y, '0', size, mode & 0X01);
                else
                    LCD_ShowChar(x + (size / 2) * t, y, ' ', size, mode & 0X01);
                continue;
            }
            else
                enshow = 1;
        }
        LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, mode & 0X01);
    }
}

void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p)
{
    uint8_t x0 = x;
    width += x;
    height += y;
    while ((*p <= '~') && (*p >= ' '))
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }
        if (y >= height)
            break; // 退出
        LCD_ShowChar(x, y, *p, size, 0);
        x += size / 2;
        p++;
    }
}

void LCD_SetWindows(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height)
{
#if TFT_X_OFFSET
    startX += TFT_X_OFFSET;
#endif
#if TFT_Y_OFFSET
    startY += TFT_Y_OFFSET;
#endif

    LCD_WR_Reg(0x2A);
    LCD_Write_Data(startX);
    LCD_Write_Data((startX + width - 1));

    LCD_WR_Reg(0x2B);
    LCD_Write_Data(startY);
    LCD_Write_Data((startY + height - 1));
    LCD_WR_Reg(0x2C);
}

void LCD_ShowImage(const uint16_t *address, uint16_t startX, uint16_t startY)
{
    uint16_t image_width;
    uint16_t image_hight;
    uint16_t x, y;
    image_width = 240;
    image_hight = 160;
    LCD_SetWindows(startX, startY, image_width, image_hight);
    for (y = 0; y < image_hight; y++)
    {
        for (x = 0; x < image_width; x++)
        {
            LCD_Write_Data(address[y * image_width + x]);
        }
    }
}
