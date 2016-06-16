/*
 * servo.h
 *
 *  Created on: 20.07.2013
 *      Author: florian
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <avr/interrupt.h>
#include <stdint.h>


//#ifndef ANZSERVO
#define ANZSERVO			8		//Anzahl der servos
//#endif


#define DDRS			DDRD		//data direktion register
#define PORTS	 		PORTD

extern void servo_init(uint8_t pin_start_p, uint8_t pin_stop_p);
extern void set_start_pos(void);
extern void setServoPos(uint8_t servo, uint16_t pos);


#endif /* SERVO_H_ */
