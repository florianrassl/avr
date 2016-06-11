#ifndef LOOP_CONTROL 
#define LOOP_CONTROL 1


#include <stdint.h>

void loop_control_init(uint16_t f);
void loop_f(uint16_t f);
void loop_wait();

#endif
