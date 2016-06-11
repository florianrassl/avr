#ifndef __TOOL_H
#define __TOOL_H 1

#include <stdint.h>

int8_t print_data(char *args[], uint8_t argc);
int8_t lock_sticks(char *args[], uint8_t argc);
int8_t unlock_sticks(char *args[], uint8_t argc);
int8_t invert_stick(char *args[], uint8_t argc);
int8_t set_pin(char *args[], uint8_t argc);
int8_t set_scale(char *args[], uint8_t argc);
int8_t print_config(char *args[], uint8_t argc);

#endif
