#include <stdint.h>

#include "../../klib/include/nanoLed.h"

#define ERROR_MAX 100
#define RX_MAX 500
#define RX_MIN -500

volatile int16_t rc_data[4];

void pars_rc_data(char data){
  static volatile uint8_t count=0, d[3];
  static volatile int16_t *rc_data_ptr = rc_data;
  volatile int16_t tmp;

  d[0] = d[1];
  d[1] = d[2];
  d[2] = data; 
  count++;
  if(count > 3){
    if(count >= ERROR_MAX){
      count = ERROR_MAX;
      rc_data[0] = 0x00;
      rc_data[1] = 0x00;
      rc_data[2] = 0x00;
      rc_data[3] = 0x00;
    }
  }
  if(d[0]== 0x00 && d[2] == 0x00 && d[1] == 0xff){
    count=0;
    rc_data_ptr = rc_data;
    NANO_LED_OFF();
    return;
  }
  if(count== 3){
    if((d[0] ^ d[1]) == d[2]){
     tmp = d[0] | (d[1]<<8);
      if(!(tmp >RX_MAX || tmp < RX_MIN))
        *rc_data_ptr = tmp; 
      rc_data_ptr++;
      count=0;
      NANO_LED_OFF();
    }
    else{
      NANO_LED_ON();
    }
  }

  /*
  if(d0==0x00 && d1==0xff && data==0x00){
    rc_data_ptr = rc_data;
    count = 0;
    NANO_LED_OFF();
  }
  else if(count==3){
    if((d0 ^ d1) == data){
      count=0;
      *rc_data_ptr= d0 | (d1<<8);
      rc_data_ptr++; //buffer overflow
      NANO_LED_OFF();
    }
    else{
      NANO_LED_ON();
    }
  }
  else{
    count++;
    d0=d1;
	  d1=data;
  }
  */
}
