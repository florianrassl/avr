/*
 * motor.c
 *
 *  Created on: Jul 16, 2014
 *      Author: florian
 */

#include <avr/io.h>

#include "../RXB8/pars.h"
#include "../RXB8/regMap.h"

void initMotor(){
	DDRB |= (1 << DDB1)|(1 << DDB2);// PB1 and PB2 is now an output
	ICR1 = 0xFFFF;// set TOP to 16bit
	OCR1A = 0x00;
	OCR1B = 0x00;
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);// set none-inverting mode
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);// set Fast PWM mode using ICR1 as TOP
	TCCR1B |= (1 << CS10);// START the timer with no prescaler
}

void setMotorSpeed(uint8_t motor, uint16_t speed){
	if(speed>pData[MOTORMAX]){
		speed=pData[MOTORMAX];
	}
	if(motor){
		OCR1A = speed;
	}
	else{
		OCR1B = speed;
	}
}
