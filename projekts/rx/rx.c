
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#include "../../klib/uart/uart.h"
#include "../../klib/nsh/nsh.h"
#include "../../klib/include/adc.h"
#include "../../klib/include/static_malloc.h"
#include "../../klib/include/loop_control.h"

#include "pars.h"
#include "servo.h"

#define PC 0 //power control

#define print(str) charDevPutStr(&uart0Dev,(char*) str)

void init(){
  initADC();
  uart0Dev.rxChar = &pars_rc_data;
  servo_init(3, 7);
  loop_control_init(100);
}


void print_h(){
  char buff[10];
  print("c0: ");
  print(itoa(rc_data[0], buff, 10));
  print("   \tc1: ");
  print(itoa(rc_data[1], buff, 10));
  print("   \tc2: ");
  print(itoa(rc_data[2], buff, 10));
  print("   \tc3: ");
  print(itoa(rc_data[3], buff, 10));
  print("\n\r");

}

void loop(){
  print_h(); 
  setServoPos(3, rc_data[0]*2);
  setServoPos(4, rc_data[1]*2);
  setServoPos(5, rc_data[2]*2);
  setServoPos(6, rc_data[3]*2);

  loop_wait();
}

int main(){
  uart0Init();
  sei();
  
  
  //uart0Dev.rxChar = uart0Dev.putChar; //uart loop back
  init();
  while(1){
    loop();
  }
  return 0;
}
