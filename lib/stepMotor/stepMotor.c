#ifndef MCU
#define __AVR_ATmega328P__
#endif

#include <stdint.h>
#include <avr/io.h>

#include "./stepMotor.h"

uint8_t fullStepM[4] = {0b1010, 0b1001, 0b0101, 0b0110};
//uint8_t halfStepM[8] = {0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000, 0b0000};

#define SMPORT DDRD
#define PINEN0 4
#define PINEN1 5
 

void sMfullStep(uint8_t d){
	static int8_t c=0;
	if(d){
		c++;
		if(c>3)
			c=0;
	}
	else{
		c--;
		if(c<0)
			c=3;
	}
	SMPORT = (SMPORT & 0xf0) | fullStepM[c];
}

void sMenabel(){
	SMPORT |= (1<<PINEN0) | (1<<PINEN1);
}

void sMdisabel(){
	 SMPORT &= ~(1<<PINEN0) | ~(1<<PINEN1);
}

void sMbreak(){
	SMPORT &= 0xf0;
}

void sMhold(){

}
