/*
 * gyro.h
 *
 *  Created on: 10.09.2013
 *      Author: florian
 */

#ifndef GYRO_H_
#define GYRO_H_

#include <stdint.h>

#define GX 0
#define GY 1
#define GZ 2

extern void l3G4200DInit();
extern void l3G4200DRefresh();
extern int16_t *l3G4200DgetData();

#endif /* GYRO_H_ */
