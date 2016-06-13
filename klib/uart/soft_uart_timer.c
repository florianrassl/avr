#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/charDev.h"

#define BAUD 9600
#define STOP_BITS 1

static volatile uint8_t soft_tx_pin;
static volatile uint8_t *soft_tx_ddr;
static volatile uint8_t *soft_tx_port;

#define MICROSECONDS_OVERHEAD_ADJUST 0

//#define ERG_TIME (((16000000ul / 8) / BAUD) - MICROSECONDS_OVERHEAD_ADJUST)
#define ERG_TIME 208

#include "../nsh/nsh.h"

void soft_uart_timer_put_char(char c);

charDev soft_uart_timer_dev;


static inline void start_timer(){
  TCCR0B |= (1 << CS01);// set prescaler to 8 and start the timer
}

static inline void stop_timer(){
  TCCR0B &= ~(1 << CS01);
}

void soft_uart_timer_init(volatile uint8_t *stp, volatile uint8_t *std, uint8_t pin) {
  soft_tx_pin = pin;
  soft_tx_ddr = std;
  soft_tx_port = stp;

  soft_uart_timer_dev.putChar = &soft_uart_timer_put_char;
  soft_uart_timer_dev.getChar = NULL;
  soft_uart_timer_dev.rxChar = NULL;

  *soft_tx_port |= (1<<soft_tx_pin);
  *soft_tx_ddr |= (1<<soft_tx_pin);
  
  TCCR0B |= (1 << WGM01);// Mode 4, CTC on OCR1A
  TIMSK0 |= (1 << OCIE0A);//Set interrupt on compare match
  OCR0A = ERG_TIME;
  char buff[10];
  nprint("###########");
  nprint(itoa(ERG_TIME, buff, 10));
}

static volatile uint16_t tx_bits;
static volatile uint16_t bit_mask;
static volatile uint8_t wait;

void wait_vor_timer(){
  while(wait==1);
}

void soft_uart_timer_put_char(char c){
  wait_vor_timer();
  wait=1;
  
  tx_bits=c;
  tx_bits |= (3<<8);
  bit_mask = 0x01;
  TCNT0=0x00;
  start_timer();
  *soft_tx_port &= ~(1<<soft_tx_pin);
}

ISR(TIMER0_COMPA_vect){
  
  if (tx_bits & bit_mask) {
    *soft_tx_port |= (1<<soft_tx_pin);
    //nprint("A");
  }
  else {
    *soft_tx_port &= ~(1<<soft_tx_pin);
    //nprint("B");
  }
  bit_mask <<= 1;
  //nprint("# ");
  if(bit_mask & (1 << 9)){
    //*soft_tx_port |= (1<<soft_tx_pin);
    stop_timer();
    wait=0;
    //nprint("fuck you");
    //send next char
  }
  //
}
