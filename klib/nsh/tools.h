#ifndef _TOOLS
#define _TOOLS 1

#ifdef _ADCTOOL
#include "../include/adc.h"
static int8_t adcTool(char *args[], uint8_t argc){
  int8_t r;
  char buff[10];
  r=getArgNum(args, argc, "-h", 1); 
  if(r>=0){
    nprint("adc Nr | -i | -m x\n\r");
    return 0;
  }
  r=getArgNum(args, argc, "-i", 1); 
  if(r>=0){
    initADC();
    return 0;
  }
  r=getArgNum(args, argc, "-m", 2);
  if(r>=0){
    nprint("pin: ");
    nprint(args[r+1]);
    nprint("  ");
    nprint(itoa(getADCData(atoi(args[r+1])), buff, 10));
    nprint("\n\r");
    return 1;
  }
  if(argc <1){
    for(r=0; r<8; r++){
      nprint(itoa(r, buff, 10));
      nprint("  ");
      nprint(itoa(getADCData(r), buff, 10));
      nprint("\n\r");
    }
  }
  return 0;
}
#endif

#ifdef _SERVOTOOL
#include "../servo/servo.h"

static int8_t servoTool(char *args[], uint8_t argc){
  int8_t r;
  r=getArgNum(args, argc, "-h", 1); 
  if(r>=0){
    nprint("servo Nr 0-1000 || servo -i\n\r");
    return 0;
  }
  r=getArgNum(args, argc, "-i", 1); 
  if(r>=0){
    servo_init();
    set_start_pos();
    return 0;
  }
  if(argc <2)
    return 0;
  setServoPos(atoi(args[0]), atoi(args[1]));
  return 0;
}
#endif


#ifdef _PORTTOOL
#include <avr/io.h>

static int8_t portTool(char *args[], uint8_t argc){
  int8_t r;
  r=getArgNum(args, argc, "-h", 1); 
  if(r>=0){
    nprint("port -'b/c/d' \"value\"\n\r");
  }
  r=getArgNum(args, argc, "-b", 2); 
  if(r>=0){
    PORTB = (int8_t)atoi(args[1]);
  }
  r=getArgNum(args, argc, "-c", 2); 
  if(r>=0){
    PORTC = (int8_t)atoi(args[1]);
  }
  r=getArgNum(args, argc, "-d", 2); 
  if(r>=0){
    PORTD = (int8_t)atoi(args[1]);
  }
  return 0;
}
#endif



#endif
