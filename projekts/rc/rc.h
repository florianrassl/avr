#ifndef __RC
#define __RC 1

#define RES 500 

typedef struct {
  uint8_t pin;
  uint16_t raw_data;
  uint16_t max;
  uint16_t min;
  uint8_t invert;
  int16_t mid_null;//not in use now
  int16_t cal_data;
}stick;

#endif
