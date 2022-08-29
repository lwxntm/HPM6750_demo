#pragma once

extern uint32_t mchtmr_ticks;
void bsp_mchtmr_init(void);
uint32_t bsp_mchtmr_get_ticks();