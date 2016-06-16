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

#define ERG_TIME (((16000000ul / 8) / BAUD) - MICROSECONDS_OVERHEAD_ADJUST)
//#define ERG_TIME 200 //is the perfect time for a F_CPU of 16MHz ans an prescaler of 8


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
  
  TCCR0A |= (1 << WGM01);// Mode 4, CTC on OCR1A
  TIMSK0 |= (1 << OCIE0A);//Set interrupt on compare match
  OCR0A = ERG_TIME;
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
 
  tx_bits = 0;
  tx_bits |= (0<<0); //start bit

  tx_bits |= (c<<1); //data bits

  /*
  tx_bits |= (1<<1);  //dbit 0
  tx_bits |= (0<<2);  //dbit 1
  tx_bits |= (0<<3);  //dbit 2
  tx_bits |= (0<<4);  //dbit 3
  tx_bits |= (0<<5);  //dbit 4
  tx_bits |= (0<<6);  //dbit 5
  tx_bits |= (1<<7);  //dbit 6
  tx_bits |= (0<<8);  //dbit 7

  */

  tx_bits  |= (1<<9);  //stop bit

  bit_mask = 0x01;
  TCNT0=0x00;
  start_timer();
}

#define BLOCK_SIZE_MAX 100
#include <string.h>
#include "../nsh/nsh.h"

static volatile char block_data[BLOCK_SIZE_MAX];
static volatile char *block_data_ptr = block_data;
static volatile uint8_t block_size = 0;
static volatile uint8_t wait_block;


void wait_send_block(){
  while(wait_block);
}

void send_block(void *block, uint8_t size){
  wait_send_block();
  wait_block=1;
  if(size > BLOCK_SIZE_MAX)
    size=BLOCK_SIZE_MAX;
  block_size = size;
  memcpy((void*)block_data, block, size);
  block_data_ptr=block_data;
  //nprint(block_data);
  soft_uart_timer_put_char(*block_data_ptr++);
}



ISR(TIMER0_COMPA_vect){
  
  if (tx_bits & bit_mask) {
    *soft_tx_port |= (1<<soft_tx_pin);
  }
  else {
    *soft_tx_port &= ~(1<<soft_tx_pin);
  }
  bit_mask <<= 1;
  if(bit_mask & (1 << 10)){
    stop_timer();
    wait=0;
    if(block_data_ptr!=block_data+block_size){
      soft_uart_timer_put_char(*block_data_ptr++);
    }
    else{
      wait_block=0;
    }
  }
  //
}
