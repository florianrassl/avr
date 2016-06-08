/*
 * adxl345.h
 *
 *  Created on: 11.05.2014
 *      Author: florian
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include <stdint.h>

#define AX 0
#define AY 1
#define AZ 2

extern void init_adxl345();
extern void adxlRefresh();
extern int16_t *getAdxlData();

#endif /* ADXL345_H_ */
