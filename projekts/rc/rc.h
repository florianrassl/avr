#ifndef __RC
#define __RC 1

typedef struct {
  uint8_t pin;
  uint16_t scale;
  uint16_t raw_data;
  uint16_t max;
  uint16_t min;
  uint8_t invert;
  uint8_t mid_null;
  uint8_t locked;
  int16_t cal_data;
}stick;

extern stick sticks[4];
void loop();

#endif
