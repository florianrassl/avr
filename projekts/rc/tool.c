#include <stdint.h>
#include <stdlib.h>


#include "rc.h"
#include "../../klib/nsh/nsh.h"

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

int8_t lock_sticks(char *args[], uint8_t argc){
  uint8_t i;
  for(i=0; i<4; i++){
    sticks[i].locked=1;
  }
  return 0;
}

int8_t unlock_sticks(char *args[], uint8_t argc){
  uint8_t i;
  for(i=0; i<4; i++){
    sticks[i].locked=0;
  }
  return 0;
}

int8_t invert_stick(char *args[], uint8_t argc){
  uint8_t i;
  i=atoi(args[0]);
  if(i>3)
    return 0;
  sticks[i].invert^=1;
  return 0;
}

int8_t set_pin(char *args[], uint8_t argc){
  uint8_t i, j;
  i=atoi(args[0]);
  j=atoi(args[1]);
  if(i>3)
    return 0;
  if(j<1 || j>4)
    return 0;
  sticks[i].pin=j;
  return 0;
}

int8_t set_scale(char *args[], uint8_t argc){
  uint8_t i;
  if(argc != 2){
    nprint("ERROR use stick i scale j\n\r");\
    return 0;
  }
  i=atoi(args[0]);
  if(i>3)
    return 0;
  sticks[i].scale=atoi(args[1]);
  return 0;
}

int8_t togel_mid_null(char *args[], uint8_t argc){
  uint8_t i;
  if(argc != 1){
    nprint("ERROR use stick i\n\r");\
    return 0;
  }
  i=atoi(args[0]);
  if(i>3)
    return 0;
  sticks[i].mid_null ^= 1;
  return 0;
}

int8_t print_config(char *args[], uint8_t argc){
  char buff[10];
  uint8_t i;
  for(i=0; i<4; i++){
    nprint("\n\rc: ");
    nprint(itoa(i, buff, 10));
    nprint("\n\rpin: ");
    nprint(itoa(sticks[i].pin, buff, 10));
    nprint("\n\rscale: ");
    nprint(itoa(sticks[i].scale, buff, 10));
    nprint("\n\rinvert: ");
    nprint(itoa(sticks[i].invert, buff, 10));
    nprint("\n\rmid null: ");
    nprint(itoa(sticks[i].mid_null, buff, 10));
    nprint("\n\rlocked: ");
    nprint(itoa(sticks[i].locked, buff, 10));
    nprint("\r\n");
  }
  return 0;
}
