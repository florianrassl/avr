#ifndef _SOFTUART
#define _SOFTUART 1

#include <util/delay.h>
#include <stdint.h>
#include "./charDev.h"

#define BAUD 9600
#define STOP_BITS 1

static uint8_t soft_tx_pin;
static uint8_t soft_tx_ddr;
static uint8_t soft_tx_port;

#define MICROSECONDS_OVERHEAD_ADJUST 0

#define MICROSECONDS_PER_BIT ((16000000ul / BAUD) - MICROSECONDS_OVERHEAD_ADJUST)

void softUartInit(volatile uint8_t stp, volatile uint8_t std, uint8_t pin);
void softUartPutChar(char c);

charDev softUartDev;

void softUartInit(volatile uint8_t stp, volatile uint8_t std, uint8_t pin) {
  soft_tx_pin = pin;
  soft_tx_ddr = std;
  soft_tx_port = stp;

  softUartDev.putChar = &softUartPutChar;
  softUartDev.getChar = NULL;
  softUartDev.rxChar = NULL;

  soft_tx_port |= (1<<soft_tx_pin);
  soft_tx_ddr |= (1<<soft_tx_pin);
}

void softUartPutChar (char c) {

  uint8_t  bit_mask;

  // start bit
  soft_tx_port &= ~(1<<soft_tx_pin);
  _delay_us(MICROSECONDS_PER_BIT);

  // data bits
  for (bit_mask=0x01; bit_mask; bit_mask<<=1) {
    if (c & bit_mask) {
      soft_tx_port |= (1<<soft_tx_pin);
    }
    else {
      soft_tx_port &= ~(1<<soft_tx_pin);
    }
    _delay_us(MICROSECONDS_PER_BIT);
  }

  // stop bit(s)
  soft_tx_port |= (1<<soft_tx_pin);
  _delay_us(MICROSECONDS_PER_BIT * STOP_BITS);
}
#endif /*_SOFTUART*/
