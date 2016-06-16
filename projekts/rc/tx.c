#include "../../klib/include/soft_uart_timer.h"
#include "./rc.h"

//bit0, bit1, xor-bit01, ... ... ... , pause, bit0, bit1 ...

void send_data(){
  static uint8_t data[15];
  uint8_t i;
  data[0] = 0x00;
  data[1] = 0xff;
  data[2] = 0x00;
  
  for(i=0; i<4; i++){
    data[(i+1)*3] = sticks[i].cal_data & 0x00ff;
    data[(i+1)*3+1] = ((sticks[i].cal_data & 0xff00)>>8);
    data[(i+1)*3+2] = data[(i+1)*3] ^ data[(i+1)*3+1];
  }
  send_block((void*)data, 15);
  
}
