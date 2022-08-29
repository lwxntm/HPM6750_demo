/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_debug_console.h"
#include "hpm_spi_drv.h"
#include <stdio.h>

#include "bsp_board_spi2.h"
#include "bsp_lcd.h"
#include "bsp_mchtmr.h"
hpm_stat_t stat;

uint32_t tmp0 = 0;
int main(void) {
  int u;
  board_init();      // SDK自身的初始化
  bsp_lcd_init();    // LCD的初始化
  bsp_mchtmr_init(); // mchtmr的初始化，用于提供系统滴答时钟
  while (1) {
    mchtmr_ticks = 0;
    for (uint32_t i = 0; i < 25; i++) {
      LCD_Clear(RED);
      LCD_Clear(BLUE);
      LCD_Clear(GREEN);
      LCD_Clear(GRED);
    }
    tmp0 = bsp_mchtmr_get_ticks();
    printf("刷屏100次耗时：%d  ms \n", tmp0);
  }
}