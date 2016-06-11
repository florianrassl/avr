#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define f_timer 16000000/1024

#ifdef DEBUG
#include <stdlib.h>
#include "../nsh/nsh.h"
#endif

volatile uint8_t __f;
uint8_t soft_presc;

void loop_f(uint16_t f);

void loop_control_init(uint16_t f){
  loop_f(f);
  TCCR2A |= (1 << WGM21);
  TIMSK2 |= (1 << OCIE2A);
  TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); //prescaler to 1024
}

void loop_f(uint16_t f){
  uint16_t count;
  count = (f_timer)/(f);
  soft_presc = count/0xff;
  if(soft_presc==0) soft_presc=1;
  if(count>=0xff)
    OCR2A = 0xff;
  else if(count==0)
    OCR2A = 1;
  else
   OCR2A = count;
}

void loop_wait(){
  #ifdef DEBUG
  if(!__f)
    nprint("loop_max\n\r");
  #endif
  while(__f);
  __f=soft_presc;
}

ISR (TIMER2_COMPA_vect){
  if(__f==0)
    return;
  __f--;
}

