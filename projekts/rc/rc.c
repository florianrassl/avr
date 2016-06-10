
#include <avr/interrupt.h>
#include <stdlib.h>

#include "../../klib/uart/uart.h"
#include "../../klib/nsh/nsh.h"
#include "../../klib/include/adc.h"
#include "../../klib/include/static_malloc.h"

#include "rc.h"
#include "prof.h"
#include "calc.h"

#define s_malloc 50

#define PC 0 //power control

void loop();

stick sticks[4];

int8_t print_data(char *args[], uint8_t argc){
  char buff[10];
  nprint("c0: ");
  nprint(itoa(sticks[0].cal_data, buff, 10));
  nprint("   \tc1: ");
  nprint(itoa(sticks[1].cal_data, buff, 10));
  nprint("   \tc2: ");
  nprint(itoa(sticks[2].cal_data, buff, 10));
  nprint("   \tc3: ");
  nprint(itoa(sticks[3].cal_data, buff, 10));
  nprint("\n\r");
  loop();
  return 1;
}

void init(){
  addTool(&print_data, "print", NULL);
  load_prof(0, sticks);
  initADC();
}

void loop(){
  update_raw_data(sticks);
  scale_to_res(sticks);
}

int main(){
  static uint8_t malloc_d[s_malloc];
  init_static_malloc(malloc_d, s_malloc);
  uart0Init();
  sei();

  nshInit(&uart0Dev);
  init();
  while(1){
    nshUpdate();
    loop();
  }
  return 0;
}
