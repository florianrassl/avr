/*
 * i2cSens.h
 *
 *  Created on: 11.05.2014
 *      Author: florian
 */

#ifndef I2CSENS_H_
#define I2CSENS_H_

#include <stdint.h>
#include "i2cmaster.h"

extern void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val);
extern int16_t readRegister(uint8_t deviceAddress, uint8_t address);

#endif /* I2CSENS_H_ */
