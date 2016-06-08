
#include <avr/interrupt.h>

#include "../../klib/uart/uart.h"
#include "../../klib/nsh/nsh.h"
#include "../../klib/include/adc.h"
#include "../../klib/include/static_malloc.h"

#define s_malloc 50

#define C0 0 //left stick left/right
#define C1 1 //left stick up/down
#define C2 2 //right stick left/right
#define C3 3 //right stick up/down

#define C0OFSET 0
#define C1OFSET 0
#define C2OFSET 0
#define C3OFSET 0

#define PC 4 //power control

int16_t CX[4]={C0, C1, C2, C3}; 
int16_t CXOFSET[4]={C0OFSET, C1OFSET, C2OFSET, C3OFSET};

void init(){
  initADC();
}

void loop(){
  int16_t controls[4]={0,0,0,0};
  uint8_t i;
  for(i=0; i<4; i++){
    controls[i]=getADCData(CX[i])+CXOFSET[i];
  }
  
  

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
