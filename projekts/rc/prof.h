#ifndef __PROF
#define __PROF 1

#include <stdint.h>


inline void load_prof(uint8_t prof_nr, stick *sticks){
  //uint8_t i;
  if(prof_nr == 0 )
    prof_nr = 0;//get_default_prof_nr();

  sticks[0].pin = 1;
  sticks[0].invert = 1;
  sticks[0].max = 500;
  sticks[0].min = 500;
  sticks[0].mid_null = 1;

  sticks[1].pin = 2;
  sticks[1].invert = 1;
  sticks[1].max = 500;
  sticks[1].min = 500;
  sticks[1].mid_null = 1;

  sticks[2].pin = 3;
  sticks[2].invert = 0;
  sticks[2].max = 500;
  sticks[2].min = 500;
  sticks[2].mid_null = 1;

  sticks[3].pin = 4;
  sticks[3].invert = 1;
  sticks[3].max = 500;
  sticks[3].min = 500;
  sticks[3].mid_null = 0;

  return;
}

#endif
