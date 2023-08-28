#ifndef __LCD_H__
#define __LCD_H__

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "main.h"

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint16_t id;
    uint8_t dir;
    uint16_t wramcmd;
    uint16_t setxcmd;
    uint16_t setycmd;
} _lcd_dev;

extern _lcd_dev lcddev;

extern uint16_t POINT_COLOR;
extern uint16_t BACK_COLOR;

//////////////////////////////////////////////////////////////////////////////////
#define LCD_LED_ON HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET)
#define LCD_LED_OFF HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET)

//--1
#define LCD_CS_SET HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define LCD_RES_SET HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET)
#define LCD_A0_SET HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)
#define LCD_SDA_SET HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_SET)
#define LCD_SCL_SET HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_SET)

//--0
#define LCD_CS_CLR HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_RES_CLR HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET)
#define LCD_A0_CLR HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_SDA_CLR HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_RESET)
#define LCD_SCL_CLR HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_RESET)
//////////////////////////////////////////////////////////////////////////////////

#define L2R_U2D 0
#define L2R_D2U 1
#define R2L_U2D 2
#define R2L_D2U 3

#define U2D_L2R 4
#define U2D_R2L 5
#define D2U_L2R 6
#define D2U_R2L 7

#define DFT_SCAN_DIR L2R_U2D

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430

#define DARKBLUE 0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE 0X5458

#define LIGHTGREEN 0X841F
#define LGRAY 0XC618

#define LGRAYBLUE 0XA651
#define LBBLUE 0X2B12

#define SSD_HOR_RESOLUTION 240
#define SSD_VER_RESOLUTION 320

#define SSD_HOR_PULSE_WIDTH 1
#define SSD_HOR_BACK_PORCH 210
#define SSD_HOR_FRONT_PORCH 45

#define SSD_VER_PULSE_WIDTH 1
#define SSD_VER_BACK_PORCH 34
#define SSD_VER_FRONT_PORCH 10

#define SSD_HT (SSD_HOR_RESOLUTION + SSD_HOR_PULSE_WIDTH + SSD_HOR_BACK_PORCH + SSD_HOR_FRONT_PORCH)
#define SSD_HPS (SSD_HOR_PULSE_WIDTH + SSD_HOR_BACK_PORCH)
#define SSD_VT (SSD_VER_PULSE_WIDTH + SSD_VER_BACK_PORCH + SSD_VER_FRONT_PORCH + SSD_VER_RESOLUTION)
#define SSD_VSP (SSD_VER_PULSE_WIDTH + SSD_VER_BACK_PORCH)

void LCD_WR_DATA(uint16_t data);
void LCD_WR_REG(uint16_t regval);
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_Fast_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y);
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Clear(uint16_t color);
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode);
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size);
void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode);
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p);
void LCD_ShowImage(const uint16_t *address, uint16_t startX, uint16_t startY);

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint16_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
void LCD_Scan_Dir(uint8_t dir);
void LCD_Display_Dir(uint8_t dir);

#endif /* __LCD_H__ */
