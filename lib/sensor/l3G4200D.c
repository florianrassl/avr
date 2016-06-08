/*
 * gyro.c
 *
 *  Created on: 08.09.2013
 *      Author: florian
 */

#include "./../twi_master/i2cmaster.h"
#include "../twi_master/twiBase.h"
#include <util/delay.h>

//#define L3G4200D_Address 208
#define L3G4200D_Address 210
//#define L3G4200D_Address 104 //I2C address of the L3G4200D

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24



int16_t data[3];

void setupL3G4200D(uint16_t scale);

//void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val);
//int16_t readRegister(uint8_t deviceAddress, uint8_t address);

void l3G4200DRefresh(){
	data[GX] = ((readRegister(L3G4200D_Address, 0x29) << 8) | readRegister(L3G4200D_Address, 0x28));
	data[GY] = ((readRegister(L3G4200D_Address, 0x2B) << 8) | readRegister(L3G4200D_Address, 0x2A));
	data[GZ] = ((readRegister(L3G4200D_Address, 0x2D) << 8) | readRegister(L3G4200D_Address, 0x2C));
}

int16_t *l3G4200DGetData(){
	return data;
}

void l3G4200DInit(){

	setupL3G4200D(500); // Configure L3G4200  - 250, 500 or 2000 deg/sec
	_delay_ms(1000);

}



void setupL3G4200D(uint16_t scale){

	// Enable x, y, z and turn off power down:
	writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

	// If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
	writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

	// Configure CTRL_REG3 to generate data ready interrupt on INT2
	// No interrupts used on INT1, if you'd like to configure INT1
	// or INT2 otherwise, consult the datasheet:
	writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

	// CTRL_REG4 controls the full-scale range, among other things:

	if(scale == 250){
		writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
	}else if(scale == 500){
		writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
	}else{
		writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
	}

	// CTRL_REG5 controls high-pass filtering of outputs, use it
	// if you'd like:
	writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}
