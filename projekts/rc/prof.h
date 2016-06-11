#ifndef __PROF
#define __PROF 1

#include <stdint.h>

#include "rc.h"

uint8_t get_default_prof();
void load_default_prof();
int8_t set_default_prof(char *args[], uint8_t argc);
int8_t save_prof(char *args[], uint8_t argc);
int8_t load_prof(char *args[], uint8_t argc);

int8_t load_defaults(char *args[], uint8_t argc);

#endif
