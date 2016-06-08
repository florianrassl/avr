/*
 * servo.h
 *
 *  Created on: 20.07.2013
 *      Author: florian
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <avr/interrupt.h>


#ifdef USERSERVO
#define ANZSERVO			8		//Anzahl der servos
#else
#define ANZSERVO			4
#endif


#define DDRS			DDRD		//data direktion register
#define PORTS	 		PORTD

#define SERVO0				0
#define SERVO1				1
#define SERVO2				2
#define SERVO3				3
#define SERVO4				4
#define SERVO5				5
#define SERVO6				6
#define SERVO7				7


extern void servo_init(void);
extern void set_start_pos(void);
extern void setServoPos(uint8_t servo, uint16_t pos);


#endif /* SERVO_H_ */
