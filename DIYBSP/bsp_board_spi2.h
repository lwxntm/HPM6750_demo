#pragma once

#include "board.h"
#include "hpm_debug_console.h"
#include "hpm_spi_drv.h"
#include <stdio.h>


typedef enum {
  spi_op_write = 0,
  spi_op_read,
  spi_op_no_data
} spi_op_t;



void board_spi2_init(void);
hpm_stat_t board_spi2_write_bytes(const uint8_t *pwbuff, uint32_t size);
hpm_stat_t board_spi2_write_read_bytes_together(uint8_t *pwbuff, uint8_t *prbuff, uint32_t size);