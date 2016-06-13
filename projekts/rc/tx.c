#include "../../klib/include/charDev.h"

#include "./rc.h"

//bit0, bit1, xor-bit01, ... ... ... , pause, bit0, bit1 ...

void send_data(charDev *c_dev){
  uint8_t data[3];
  uint8_t i;
  for(i=0; i<4; i++){
    data[0] = sticks[i].raw_data & 0xff00;
    data[1] = ((sticks[i].raw_data & 0x00ff)<<8);
    data[2] = data[0] ^ data[1];
    charDevPutBlock( c_dev, data, 3);
  }
}
