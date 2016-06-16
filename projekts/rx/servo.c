/*
 * servo.c
 *
 *  Created on: 20.07.2013
 *      Author: florian
 */

#ifndef MCU
#define __AVR_ATmega328P__ 1
#endif


#include "servo.h"
#include <avr/io.h>


volatile uint8_t servo = ANZSERVO+1;
volatile uint16_t position[8];
volatile uint8_t pin_start = 0, pin_stop = 0;
uint16_t ERG_TIME = 20000 -(ANZSERVO*2000);

void setServoPos(uint8_t servo, uint16_t pos){
	uint16_t tmp=0;
	uint8_t i;
	if(pos>1200)
		pos=1200;
	position[servo]=((pos*2)+2000);
	for(i=3; i<ANZSERVO; i++){
		tmp+=position[i];
	}
	ERG_TIME = 20000-tmp;
}

void set_start_pos(void){
	//startwerte
	position[0]=1000;
	position[1]=1000;
	position[2]=1000;
	position[3]=1000;
	position[4]=1000;
	position[5]=1000;
	position[6]=1000;
	position[7]=1000;
}

void servo_init(uint8_t pin_start_p, uint8_t pin_stop_p){
  pin_start = pin_start_p;
  pin_stop = pin_stop_p;
	DDRS |=(1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
	OCR1A = 0xffff;
	TCCR1B |= (1 << WGM12);// Mode 4, CTC on OCR1A
	TIMSK1 |= (1 << OCIE1A);//Set interrupt on compare match
	TCCR1B |= (1 << CS11);// set prescaler to 8 and start the timer
	//sei();// enable interrupts
}

ISR (TIMER1_COMPA_vect){

	PORTS &= ~(1<<servo);//pulz beenden
	servo++;
	if(!(servo<ANZSERVO+1))
		servo = pin_start;
	if(servo>=ANZSERVO){
		OCR1A = ERG_TIME;
	}
	else{
		OCR1A = position[servo];
		PORTS |= (1<<servo);//neuer pulz starten
	}
}
