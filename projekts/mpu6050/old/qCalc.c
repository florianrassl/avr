/*
 * userData.c
 *
 *  Created on: 15.05.2014
 *      Author: florian
 */
#include <stdint.h>
#include <stdlib.h>

#include "./qCalc.h"
#include "./qLage.h"
#include "./kalipriren.h"
#include "./../spi_address_logic/regMap.h"
#include "./../spi_address_logic/spi_address_logic.h"
#include "./../servo/servo.h"
#include "./../spi_address_logic/dBridge.h"
#include "./../main/main.h"


#define SENS_ROLL  10 //32
#define SENS_PITCH 10 //32
#define SENS_YAW 25

#define MAX 20 //33

#define MAX_YAW 25

int16_t userData[4]={0,0,0,0};
int16_t outN[4]= {0,0,0,0};
/*
 * outN[0] //vor zurück		; range -255 bis +255
 * outN[1] //rechts links	; range -255 bis +255
 * outN[2] //drehen			; range -255 bis +255
 * outN[3] //hoch runter	; range 0-1000
 */

void rUserData(){
	/*
	userData[ROLL] = ((address[USRREG_X] << 7) | address[USRREG_X+1])-500;
	userData[PITCH] = ((address[USRREG_Y] << 7) | address[USRREG_Y+1])-500;
	userData[YAW] = ((address[USRREG_F] << 7) | address[USRREG_F+1])-500;
	userData[SPEED] = ((address[USRREG_Z] << 7) | address[USRREG_Z+1]);
	*/
	userData[ROLL] = address[USRREG_X]*5 -250;
	userData[PITCH] = address[USRREG_Y]*5 -250;
	userData[YAW] = address[USRREG_F]*5 -250;
	userData[SPEED] = address[USRREG_Z]*10;
}

void calc(){
	//TODO beim anschluss von motoren auskomentirung auskommentieren!!!!!!!

	outN[ROLL] = getWinkelRPY()[ROLL]*SENS_ROLL + userData[ROLL];
	outN[PITCH] = getWinkelRPY()[PITCH]*SENS_PITCH + userData[PITCH];
	outN[YAW] = getWinkelRPY()[YAW]/SENS_YAW + userData[YAW];

	/*
	outN[ROLL] = getWinkelRPY()[ROLL]/SENS_ROLL + userData[ROLL];
	outN[PITCH] = getWinkelRPY()[PITCH]/SENS_PITCH + userData[PITCH];
	outN[YAW] = getWinkelRPY()[YAW]/SENS_YAW + userData[YAW];

	*/
	outN[SPEED] = userData[SPEED];
	//MAX's
	//ROLL
	if(outN[ROLL]>MAX){
		outN[ROLL] = MAX;
	}
	if(outN[ROLL]<-MAX){
		outN[ROLL] = -MAX;
	}
	//PITCH
	if(outN[PITCH]>MAX){
		outN[PITCH] = MAX;
	}
	if(outN[PITCH]<-MAX){
		outN[PITCH] = -MAX;
	}
	//YAW
	if(outN[YAW]>MAX){
		outN[YAW] = MAX;
	}
	if(outN[YAW]<-MAX){
		outN[YAW] = -MAX;
	}

	//min gesch
	if(userData[SPEED]<150){
		outN[PITCH]=0;
		outN[ROLL]=0;
		outN[YAW]=0;
		return;
	}
}

void servoOut(){
	uint8_t i;
	int16_t mSX[4];
	mSX[0] = outN[SPEED]-outN[PITCH]+outN[ROLL]+outN[YAW];
	mSX[1] = outN[SPEED]+outN[PITCH]+outN[ROLL]-outN[YAW];
	mSX[2] = outN[SPEED]+outN[PITCH]-outN[ROLL]+outN[YAW];
	mSX[3] = outN[SPEED]-outN[PITCH]-outN[ROLL]-outN[YAW];

	for(i=0; i<4; i++){
		if(mSX[i]<0)
			mSX[i] = 0;
	}

	setServoPos(SERVO0, mSX[0]); //servo rechts oben
	setServoPos(SERVO1, mSX[1]); //servo rechts unten
	setServoPos(SERVO2, mSX[2]); //servo links unten
	setServoPos(SERVO3, mSX[3]); //servo links oben
/*
	setServoPos(SERVO0, outN[SPEED]-outN[PITCH]+outN[ROLL]+outN[YAW]); //servo rechts oben
	setServoPos(SERVO1, outN[SPEED]+outN[PITCH]+outN[ROLL]-outN[YAW]); //servo rechts unten
	setServoPos(SERVO2, outN[SPEED]+outN[PITCH]-outN[ROLL]+outN[YAW]); //servo links unten
	setServoPos(SERVO3, outN[SPEED]-outN[PITCH]-outN[ROLL]-outN[YAW]); //servo links oben
*/
}

void setStartPos(){
	//uint8_t i=0;
	address[USRREG_X+1] = (uint8_t)(500 >> 7);
	address[USRREG_X] = (uint8_t)500;
	address[USRREG_Y+1] = (uint8_t)(500 >> 7);
	address[USRREG_Y] = (uint8_t)500;
}

void updateQControlCalc(){

	if(address[INIT]){
		dBOut("!!!!!INIT QUADRO_CALC!!!!!\n\n\n");
		setStartPos();
		dBOut("!!!!!KALIBRIRE!!!!!\n");
		kaliprire();
		dBOut("!!!!!KALIBRIRUNG FERTIG!!!!!\n\n\n");
		address[USRREG_X]=50;
		address[USRREG_Y]=50;
		address[USRREG_F]=50;
		address[USRREG_Z]=0;
		address[INIT] = 0;

	}
#ifdef PRINTF_DEBUG

	static char dbuff[20];
	if(!address[DBUFFE]){
		/*
		dBOut("##outN[0]:=");
		dBOut(itoa(userData[0], dbuff, 10));
		dBOut("*outN[1]:=");
		dBOut(itoa(userData[1], dbuff, 10));
		dBOut("*outN[2]:=");
		dBOut(itoa(userData[2], dbuff, 10));
		dBOut("*outN[3]:=");
		dBOut(itoa(userData[3], dbuff, 10));
		dBOut("*##\n");
		*/
		dBOut("##ROLL:=");
		dBOut(itoa(outN[0], dbuff, 10));
		dBOut("*PITCH:=");
		dBOut(itoa(outN[1], dbuff, 10));
		dBOut("*YAW:=");
		dBOut(itoa(outN[2], dbuff, 10));
		dBOut("*SPEED:=");
		dBOut(itoa(outN[3], dbuff, 10));
		dBOut("*##\n");

		/*
		dBOut("##*a1:=");
		dBOut(itoa(a1, dbuff, 10));
		dBOut("*a2:=");
		dBOut(itoa(a2, dbuff, 10));
		dBOut("*a3:=");
		dBOut(itoa(a3, dbuff, 10));
		dBOut("*##\n");
		*/
		/*
		dBOut("##*S1:=");
		dBOut(itoa(x1, dbuff, 10));
		dBOut("*S2:=");
		dBOut(itoa(x2, dbuff, 10));
		dBOut("*S3:=");
		dBOut(itoa(x3, dbuff, 10));
		dBOut("*##\n\n");
		*/

	}
#endif
	rUserData();
	calc();
	servoOut();
}

