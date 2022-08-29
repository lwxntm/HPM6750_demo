#include "bsp_lcd.h"
#include "hpm_gpio_drv.h"

/**
  pins:
  SCK&SDA= SPI2
  RESET= PF1
  DC/RS=PF2
  CS=PF0
*/

void lcd_gpio_init(void) {
  board_spi2_init(); // init SCK&SDA

  /* 初始化非SPI的GPIO */
  HPM_IOC->PAD[IOC_PAD_PF00].FUNC_CTL = IOC_PF00_FUNC_CTL_GPIO_F_00;

  gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOF, 00);
  gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOF, 00, 1);

  HPM_IOC->PAD[IOC_PAD_PF01].FUNC_CTL = IOC_PF01_FUNC_CTL_GPIO_F_01;

  gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOF, 01);
  gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOF, 01, 1);

  HPM_IOC->PAD[IOC_PAD_PF02].FUNC_CTL = IOC_PF02_FUNC_CTL_GPIO_F_02;

  gpio_set_pin_output(HPM_GPIO0, GPIO_OE_GPIOF, 02);
  gpio_write_pin(HPM_GPIO0, GPIO_DO_GPIOF, 02, 1);

  BSP_LCD_RESET_PIN(BSP_LCD_RESET_OUTPUT_PIN);
  board_delay_ms(50);
  BSP_LCD_SET_PIN(BSP_LCD_RESET_OUTPUT_PIN);
  board_delay_ms(50);
}

static void lcd_send_cmd(const uint8_t cmd) {
  BSP_LCD_RESET_PIN(BSP_LCD_DC_OUTPUT_PIN); // D/C=0, 指令
  BSP_LCD_RESET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=0

  board_spi2_write_bytes(&cmd, 1);

  BSP_LCD_SET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=1
  BSP_LCD_SET_PIN(BSP_LCD_DC_OUTPUT_PIN); // D/C=1, 数据
}

void lcd_send_single_data(const uint8_t data) {
  BSP_LCD_RESET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=0

  board_spi2_write_bytes(&data, 1);

  BSP_LCD_SET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=1
}

void lcd_send_data(const uint8_t *data, uint8_t len) {
  BSP_LCD_RESET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=0

  board_spi2_write_bytes(data, len);

  BSP_LCD_SET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=1
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void Lcd_WriteData_16Bit(u16 Data) {
  BSP_LCD_RESET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=0
  uint8_t tx_datas[2] = {0};
  tx_datas[0] = Data >> 8;
  tx_datas[1] = Data & 0xFF;
  board_spi2_write_bytes(tx_datas, 2);
  BSP_LCD_SET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=1
}

void lcd_reg_init_ili9341(void) {
  //*************2.8inch ILI9341初始化**********//
  lcd_send_cmd(0xCF);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0xC9); // C1
  lcd_send_single_data(0X30);
  lcd_send_cmd(0xED);
  lcd_send_single_data(0x64);
  lcd_send_single_data(0x03);
  lcd_send_single_data(0X12);
  lcd_send_single_data(0X81);
  lcd_send_cmd(0xE8);
  lcd_send_single_data(0x85);
  lcd_send_single_data(0x10);
  lcd_send_single_data(0x7A);
  lcd_send_cmd(0xCB);
  lcd_send_single_data(0x39);
  lcd_send_single_data(0x2C);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x34);
  lcd_send_single_data(0x02);
  lcd_send_cmd(0xF7);
  lcd_send_single_data(0x20);
  lcd_send_cmd(0xEA);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_cmd(0xC0);         // Power control
  lcd_send_single_data(0x1B); // VRH[5:0]
  lcd_send_cmd(0xC1);         // Power control
  lcd_send_single_data(0x00); // SAP[2:0];BT[3:0] 01
  lcd_send_cmd(0xC5);         // VCM control
  lcd_send_single_data(0x30); // 3F
  lcd_send_single_data(0x30); // 3C
  lcd_send_cmd(0xC7);         // VCM control2
  lcd_send_single_data(0XB7);
  lcd_send_cmd(0x36); // Memory Access Control
  lcd_send_single_data(0x08);
  lcd_send_cmd(0x3A);
  lcd_send_single_data(0x55);
  lcd_send_cmd(0xB1);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x1A);
  lcd_send_cmd(0xB6); // Display Function Control
  lcd_send_single_data(0x0A);
  lcd_send_single_data(0xA2);
  lcd_send_cmd(0xF2); // 3Gamma Function Disable
  lcd_send_single_data(0x00);
  lcd_send_cmd(0x26); // Gamma curve selected
  lcd_send_single_data(0x01);
  lcd_send_cmd(0xE0); // Set Gamma
  lcd_send_single_data(0x0F);
  lcd_send_single_data(0x2A);
  lcd_send_single_data(0x28);
  lcd_send_single_data(0x08);
  lcd_send_single_data(0x0E);
  lcd_send_single_data(0x08);
  lcd_send_single_data(0x54);
  lcd_send_single_data(0XA9);
  lcd_send_single_data(0x43);
  lcd_send_single_data(0x0A);
  lcd_send_single_data(0x0F);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_cmd(0XE1); // Set Gamma
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x15);
  lcd_send_single_data(0x17);
  lcd_send_single_data(0x07);
  lcd_send_single_data(0x11);
  lcd_send_single_data(0x06);
  lcd_send_single_data(0x2B);
  lcd_send_single_data(0x56);
  lcd_send_single_data(0x3C);
  lcd_send_single_data(0x05);
  lcd_send_single_data(0x10);
  lcd_send_single_data(0x0F);
  lcd_send_single_data(0x3F);
  lcd_send_single_data(0x3F);
  lcd_send_single_data(0x0F);
  lcd_send_cmd(0x2B);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x01);
  lcd_send_single_data(0x3f);
  lcd_send_cmd(0x2A);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0x00);
  lcd_send_single_data(0xef);
  lcd_send_cmd(0x11); // Exit Sleep
  board_delay_ms(120);
  lcd_send_cmd(0x29); // display on
}

void bsp_lcd_init(void) {
  lcd_gpio_init();
  lcd_reg_init_ili9341();
}
//设置即将要发送的图像数据将要显示到的窗口
void LCD_SetWindows(u16 xStar, u16 yStar, u16 xEnd, u16 yEnd) {
  uint8_t tx_data[4];

  /* 设置Column地址 */
  tx_data[0] = xStar >> 8;   //起始地址高8位
  tx_data[1] = xStar & 0xFF; //起始地址高8位
  tx_data[2] = xEnd >> 8;    //结束地址高8位
  tx_data[3] = xEnd & 0xFF;  //结束地址高8位
  lcd_send_cmd(0x2A);
  lcd_send_data(tx_data, 4);

  /* 设置Page地址 */
  tx_data[0] = yStar >> 8;
  tx_data[1] = yStar & 0xFF;
  tx_data[2] = yEnd >> 8;
  tx_data[3] = yEnd & 0xFF;
  lcd_send_cmd(0x2B);
  lcd_send_data(tx_data, 4);

  /* 准备写入图像数据 */
  lcd_send_cmd(0x2C);
}

void LCD_SetCursor(u16 Xpos, u16 Ypos) {
  LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

void LCD_Clear(u16 Color) {
  uint32_t i, m;
  LCD_SetWindows(0, 0, 240 - 1, 320 - 1);
  BSP_LCD_RESET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=0
  for (i = 0; i < 320; i++) {
    for (m = 0; m < 240; m++) {
      Lcd_WriteData_16Bit(Color);
    }
  }
  BSP_LCD_SET_PIN(BSP_LCD_CS_OUTPUT_PIN); // CS=0
}