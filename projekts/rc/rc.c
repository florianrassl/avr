
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#include "../../klib/uart/uart.h"
#include "../../klib/nsh/nsh.h"
#include "../../klib/include/adc.h"
#include "../../klib/include/static_malloc.h"
#include "../../klib/include/loop_control.h"
#include "../../klib/include/soft_uart_timer.h"

#include "rc.h"
#include "prof.h"
#include "calc.h"
#include "tool.h"
#include "tx.h"

#define s_malloc 200

#define PC 0 //power control

stick sticks[4];

void init(){
  addTool(&print_data, "print", NULL);
  addTool(&lock_sticks, "lock_sticks", NULL);
  addTool(&unlock_sticks, "unlock_sticks", NULL);
  addTool(&invert_stick, "invert_stick", NULL);
  addTool(&load_prof, "load_prof", NULL);
  addTool(&save_prof, "save_prof", NULL);
  addTool(&set_default_prof, "set_default_prof", NULL);
  addTool(&load_defaults, "load_defaults", NULL);
  addTool(&set_pin, "set_pin", NULL);
  addTool(&set_scale, "set_scale", NULL);
  addTool(&print_config, "p", NULL);

  load_default_prof(0, sticks);
  initADC();
  soft_uart_timer_init(&PORTB, &DDRB, 1);
  loop_control_init(10);
}

void loop(){
  update_raw_data(sticks);
  scale_to_res(sticks);
  //send_data(&softUartDev);
  //charDevPutStr(&soft_uart_timer_dev, "1");
  loop_wait();
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
