/*
 * i2cSens.c
 *
 *  Created on: 11.05.2014
 *      Author: florian
 */
#include "i2cmaster.h"

void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val) {

	i2c_start(deviceAddress+I2C_WRITE); // start transmission to device
	i2c_write(address);       // send register address
	i2c_write(val);         // send value to write
    i2c_stop();     // end transmission
}

int16_t readRegister(uint8_t deviceAddress, uint8_t address){

    int16_t v;
    i2c_start(deviceAddress+I2C_WRITE);
    i2c_write(address); // register to read
    i2c_rep_start(deviceAddress+I2C_READ); // read a byte
    v = i2c_readNak();
    i2c_stop();
    return v;
}
