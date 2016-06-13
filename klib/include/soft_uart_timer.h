#ifndef _SOFTUART
#define _SOFTUART 1

#include <stdint.h>
#include "./charDev.h"


void soft_uart_timer_init(volatile uint8_t *stp, volatile uint8_t *std, uint8_t pin);
void soft_uart_timer_put_char(char c);

extern charDev soft_uart_timer_dev;

#endif /*_SOFTUART*/
