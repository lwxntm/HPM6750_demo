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
hpm_stat_t stat;

uint8_t wbuff[10] = {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9};
uint8_t rbuff[10] = {0};

int main(void) {
  int u;
  board_init();
  board_spi2_init();
  while (1) {
    board_delay_ms(2000);
    printf("SPI-Master transfer starts.\n");
    stat = board_spi2_write_bytes((uint8_t *)wbuff, ARRAY_SIZE(wbuff));
    if (stat == status_success) {
      printf("SPI-Master transfer successful ends.\n");
    } else {
      printf("SPI-Master transfer error[%d]!\n", stat);
    }
  }
  return 0;
}