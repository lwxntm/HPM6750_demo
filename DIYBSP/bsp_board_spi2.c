#include "bsp_board_spi2.h"

void spi_transfer_mode_print(spi_control_config_t *config) {
  uint8_t trans_mode = config->common_config.trans_mode;

  char trans_mode_table[][50] = {"write-read-together",
      "write-only",
      "read-only",
      "write-read",
      "read-write",
      "write-dummy-read",
      "read-dummy-write",
      "no-data",
      "dummy-write",
      "dummy-read"};

  printf("SPI-Master transfer mode:%s\n", trans_mode_table[trans_mode]);
}


spi_timing_config_t timing_config = {0};
spi_format_config_t format_config = {0};
spi_control_config_t control_config = {0};

void board_spi2_init(void) {
  board_init_spi_clock(BOARD_APP_SPI_BASE);
  board_init_spi_pins(BOARD_APP_SPI_BASE);
  printf("SPI-Master Polling Transfer Example\n");
  /* set SPI sclk frequency for master */
  spi_master_get_default_timing_config(&timing_config);
  timing_config.master_config.clk_src_freq_in_hz = BOARD_APP_SPI_CLK_SRC_FREQ;
  timing_config.master_config.sclk_freq_in_hz = BOARD_APP_SPI_CLK_SRC_FREQ;
  spi_master_timing_init(BOARD_APP_SPI_BASE, &timing_config);
  printf("SPI-Master transfer timing is configured.\n");
  printf("SPI-Master transfer source clock frequency: %dHz\n", timing_config.master_config.clk_src_freq_in_hz);
  printf("SPI-Master tannsfer sclk frequecny: %dHz\n", timing_config.master_config.sclk_freq_in_hz);

  /* set SPI format config for master */
  spi_master_get_default_format_config(&format_config);
  // format_config.master_config.addr_len_in_bytes = BOARD_APP_SPI_ADDR_LEN_IN_BYTES;
  format_config.common_config.data_len_in_bits = 8U; //一个数据是8位
  format_config.common_config.data_merge = false;    //不懂是什么功能，不使用
  format_config.common_config.mosi_bidir = false;
  format_config.common_config.lsb = false;                            //使用MSB
  format_config.common_config.mode = spi_master_mode;                 //主机模式
  format_config.common_config.cpol = spi_sclk_low_idle;               // CPOL=0
  format_config.common_config.cpha = spi_sclk_sampling_odd_clk_edges; // CPHA=1
  spi_format_init(BOARD_APP_SPI_BASE, &format_config);                //执行初始化
  printf("SPI-Master transfer format is configured.\n");

  /* set SPI control config for master */
  spi_master_get_default_control_config(&control_config);
  control_config.master_config.cmd_enable = false;  //不懂是什么功能，不使用
  control_config.master_config.addr_enable = false; //不懂是什么功能，不使用
  control_config.master_config.addr_phase_fmt = spi_address_phase_format_single_io_mode;
  control_config.common_config.trans_mode = spi_trans_write_read_together;
  control_config.common_config.data_phase_fmt = spi_single_io_mode; //单线写
  // control_config.common_config.dummy_cnt = spi_dummy_count_1;
  spi_transfer_mode_print(&control_config);
}

/**
typedef enum {
    spi_trans_write_read_together = 0,
    spi_trans_write_only,
    spi_trans_read_only,
    spi_trans_write_read,
    spi_trans_read_write,
    spi_trans_write_dummy_read,
    spi_trans_read_dummy_write,
    spi_trans_no_data,
    spi_trans_dummy_write,
    spi_trans_dummy_read
} spi_trans_mode_t;
*/
void board_spi2_trans_mode_change(spi_trans_mode_t trans_moden) {
  if (control_config.common_config.trans_mode != trans_moden)
    control_config.common_config.trans_mode = trans_moden;
}

hpm_stat_t board_spi2_write_bytes(const uint8_t *pwbuff, uint32_t size) {
  board_spi2_trans_mode_change(spi_trans_write_only);
  hpm_stat_t stat = spi_transfer(BOARD_APP_SPI_BASE,
      &control_config,
      NULL, NULL,
      (uint8_t *)pwbuff, size, NULL, 0);
  return stat;
}

hpm_stat_t board_spi2_write_read_bytes_together(uint8_t *pwbuff, uint8_t *prbuff, uint32_t size) {
  board_spi2_trans_mode_change(spi_trans_write_read_together);
  hpm_stat_t stat = spi_transfer(BOARD_APP_SPI_BASE,
      &control_config,
      NULL, NULL,
      (uint8_t *)pwbuff, size, (uint8_t *)prbuff, size);
  return stat;
}