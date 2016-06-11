#ifndef __CALC
#define __CALC

#include <stdint.h>
#include "rc.h"

#define RES sticks[i].scale

inline void scale_to_res(stick *sticks){
  uint8_t i;
  float t;
  for(i=0; i<4; i++){
    t=sticks[i].raw_data;
    if(t > sticks[i].max)
      t = sticks[i].max;
    if(t < sticks[i].min)
      t = sticks[i].min;
    t -= sticks[i].min;
    t = t / (sticks[i].max -sticks[i].min);
    if(sticks[i].invert)
      sticks[i].cal_data = (RES)-(RES*t);
    else
      sticks[i].cal_data = RES*t;
    if(sticks[i].mid_null)
      sticks[i].cal_data -= (RES/2);
  }
}

inline void update_raw_data(stick *sticks){
  uint8_t i;
  uint16_t t;
  for(i=0; i<4; i++){
    t = getADCData(sticks[i].pin);
    sticks[i].raw_data = t;
    if(sticks[i].locked)
      continue;
    if(t<sticks[i].min)
      sticks[i].min = t;
    if(t>sticks[i].max)
      sticks[i].max =t;
  }
} 


#endif
