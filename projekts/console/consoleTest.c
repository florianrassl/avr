
#include <avr/interrupt.h>
#include <stdlib.h>

#include "../../klib/uart/uart.h"
#include "../../klib/nsh/nsh.h"
#include "../../klib/include/static_malloc.h"

#define s_malloc 50

int main(){

  static uint8_t malloc_d[s_malloc];
  init_static_malloc(malloc_d, s_malloc);
  uart0Init();
  sei();

  nshInit(&uart0Dev);

  while(1){
    nshUpdate();
  }
  return 0;
}
