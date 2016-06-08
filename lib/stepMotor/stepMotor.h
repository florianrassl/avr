
#ifndef _STEPMOTOR
#define _STEPMOTOR 1

#include <stdint.h>

#define R 0
#define L 1

extern void sMfullStep(uint8_t d);
extern void sMenabel();
extern void sMdisabel();
extern void sMbreak();
extern void sMhold();



#endif /*STEPMOTOR*/
