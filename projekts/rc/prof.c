#include <avr/eeprom.h>
#include <stdint.h>
#include <stdlib.h>

#include "prof.h"
#include "rc.h"

#define PROF_START 100
#define PROF_SIZE 100
#define DEFAULT_PROF 10

uint8_t get_default_prof(){
  eeprom_busy_wait();
  return eeprom_read_byte ((uint8_t*)DEFAULT_PROF);
}

int8_t set_default_prof(char *args[], uint8_t argc){
  eeprom_busy_wait();
  eeprom_write_byte ((uint8_t*)DEFAULT_PROF, (uint8_t)atoi(args[0]));
  return 0;
}

int8_t save_prof(char *args[], uint8_t argc){
  eeprom_busy_wait();
  eeprom_write_block((void*) sticks, (uint8_t*)(PROF_START+PROF_SIZE*atoi(args[0])), sizeof(sticks));
  return 0;
}

int8_t load_prof(char *args[], uint8_t argc){
  eeprom_busy_wait();
  eeprom_read_block(sticks, (uint8_t*)(PROF_START+PROF_SIZE*atoi(args[0])), sizeof(sticks));
  return 0;
}

void load_default_prof(){
  eeprom_busy_wait();
  eeprom_read_block(sticks, (uint8_t*)(get_default_prof()*PROF_SIZE+PROF_START), sizeof(sticks));
}

int8_t load_defaults(char *args[], uint8_t argc){

  sticks[0].pin = 1;
  sticks[0].invert = 1;
  sticks[0].max = 500;
  sticks[0].min = 500;
  sticks[0].mid_null = 1;
  sticks[0].scale = 500;

  sticks[1].pin = 2;
  sticks[1].invert = 1;
  sticks[1].max = 500;
  sticks[1].min = 500;
  sticks[1].mid_null = 1;
  sticks[1].scale = 500;

  sticks[2].pin = 3;
  sticks[2].invert = 0;
  sticks[2].max = 500;
  sticks[2].min = 500;
  sticks[2].mid_null = 1;
  sticks[2].scale = 500;

  sticks[3].pin = 4;
  sticks[3].invert = 1;
  sticks[3].max = 500;
  sticks[3].min = 500;
  sticks[3].mid_null = 0;
  sticks[3].scale = 500;
  return 0;
}

