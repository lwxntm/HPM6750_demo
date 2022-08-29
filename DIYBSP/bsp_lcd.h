#pragma once

#include "board.h"
#include "hpm_debug_console.h"
#include "hpm_spi_drv.h"
#include <stdio.h>
#include "bsp_board_spi2.h"



#define  BSP_LCD_CS_OUTPUT_PORT GPIO_OE_GPIOF
#define  BSP_LCD_CS_OUTPUT_PIN 0


#define  BSP_LCD_RESET_OUTPUT_PORT GPIO_OE_GPIOF
#define  BSP_LCD_RESET_OUTPUT_PIN 1

#define  BSP_LCD_DC_OUTPUT_PORT GPIO_OE_GPIOF
#define  BSP_LCD_DC_OUTPUT_PIN 2

#define  BSP_LCD_SET_PIN(x) (HPM_GPIO0->DO[GPIO_DO_GPIOF].SET = 1 << x)
#define  BSP_LCD_RESET_PIN(x) (HPM_GPIO0->DO[GPIO_DO_GPIOF].CLEAR = 1 << x)



//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
	    					


void bsp_lcd_init(void);
void LCD_Clear(u16 Color);