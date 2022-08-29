#include "board.h"
#include "hpm_clock_drv.h"
#include "hpm_debug_console.h"
#include "hpm_gpio_drv.h"
#include "hpm_mchtmr_drv.h"
#include <stdio.h>

uint32_t mchtmr_ticks = 0;
uint32_t mchtmr_freq = 0;

#define PERIOD_IN_MS (1)
#ifndef MCHTMR_CLK_NAME
#define MCHTMR_CLK_NAME (clock_mchtmr0)
#endif

static inline void mchtmr_delay_ms(uint32_t ms) {
  mchtmr_delay(HPM_MCHTMR, (uint64_t)ms * mchtmr_freq / 1000);
}

void isr_mchtmr(void) {
  mchtmr_ticks++;
  mchtmr_delay_ms(PERIOD_IN_MS);
}

SDK_DECLARE_MCHTMR_ISR(isr_mchtmr)

void bsp_mchtmr_init(void) {
  /* make sure mchtmr will not be gated on "wfi" */
  board_ungate_mchtmr_at_lp_mode();
  mchtmr_freq = clock_get_frequency(MCHTMR_CLK_NAME);
  enable_mchtmr_irq();
  mchtmr_delay_ms(PERIOD_IN_MS);
}

uint32_t bsp_mchtmr_get_ticks() {
  return mchtmr_ticks;
}