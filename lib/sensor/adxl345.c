/*
 * besch.c
 *
 *  Created on: 09.09.2013
 *      Author: florian
 */


#include <avr/io.h>
#include <util/delay.h>

#include "./adxl345.h"
#include "./../twi_master/i2cmaster.h"
#include "../twi_master/twiBase.h"

#define ADXL345Address 0xA6

#define FIFO_CTL 0x38 // muss null sein
#define DATA_FORMAT 0x31
#define POWER_CTL 0x2D

#define DATAX0 0x32
#define DATAX1 0x33

#define DATAY0 0x34
#define DATAY1 0x35

#define DATAZ0 0x36
#define DATAZ1 0x37


//void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val);
//int16_t readRegister(uint8_t deviceAddress, uint8_t address);

int16_t data[3];

void init_adxl345(){
	DDRB |= (1<<1);  //into i2c modus cs = 1
	PORTB |=(1<<1);

	_delay_ms(200);
	writeRegister(ADXL345Address, FIFO_CTL, 0x00);
	//writeRegister(ADXL345Address, DATA_FORMAT, 0x0A);
	writeRegister(ADXL345Address, DATA_FORMAT, 0x00);
	writeRegister(ADXL345Address, POWER_CTL, 0x08);
	_delay_ms(2000);

}

int16_t *getAdxlData(){
	return data;
}

void adxlRefresh(){
	data[AX] = ((readRegister(ADXL345Address, DATAX0) << 8) | readRegister(ADXL345Address, DATAX1));
	data[AY] = ((readRegister(ADXL345Address, DATAY0) << 8) | readRegister(ADXL345Address, DATAY1));
	data[AZ] = ((readRegister(ADXL345Address, DATAZ0) << 8) | readRegister(ADXL345Address, DATAZ1));
}
