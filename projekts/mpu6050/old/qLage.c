/*
 * qControlCalc.c
 *
 *  Created on: 14.05.2014
 *      Author: florian
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

#include "./qLage.h"
#include "./../sensor/gyro.h"
#include "./../sensor/adxl345.h"
#include "./../main/main.h"
#include "./../spi_address_logic/spi_address_logic.h"
#include "./../spi_address_logic/regMap.h"
#include "./../spi_address_logic/dBridge.h"
#include "./kalipriren.h"


int16_t WinkelRPY[3]={0,0,0};
//#define TimeConst 0.02
#define TimeConst 0.2
#define MixAcc 0.97
//#define MixAcc 0.3


void init_qControl(){
}
/*
 * winkel = (0.97) * (winkel + gyro*dt) + (0.03) * (acc) komplimänter filter abwandel und einbauen!
 *
 *istAngle=a*(istAngle+istGyro*FilterTime) + (1-a)*istACC
 *
 */

char dbuff[20];
void calcWinkel(){

/*
	WinkelRPY[ROLL] =MixAcc*(WinkelRPY[ROLL]+getKaliprirtGyro()[GX]*TimeConst) + (1-MixAcc)*getKaliprirtAdxl()[AX];
	WinkelRPY[PITCH] =MixAcc*(WinkelRPY[PITCH]+getKaliprirtGyro()[GY]*TimeConst) + (1-MixAcc)*getKaliprirtAdxl()[AY];
	WinkelRPY[YAW] =(WinkelRPY[YAW]+getKaliprirtGyro()[GZ]*TimeConst);
*/
/*
	WinkelRPY[ROLL] =(WinkelRPY[ROLL]+getKaliprirtGyro()[GX]*TimeConst);
	WinkelRPY[PITCH] =(WinkelRPY[PITCH]+getKaliprirtGyro()[GY]*TimeConst);
	WinkelRPY[YAW] =(WinkelRPY[YAW]+getKaliprirtGyro()[GZ]*TimeConst);
	*/

	WinkelRPY[ROLL] =(WinkelRPY[ROLL]+(getKaliprirtGyro()[GX]/85));
	WinkelRPY[PITCH] =(WinkelRPY[PITCH]+getKaliprirtGyro()[GY]/85);
	WinkelRPY[YAW] =(WinkelRPY[YAW]+(getKaliprirtGyro()[GZ]/70));
/*
	if(!address[DBUFFE]){

		dBOut("R");
		dBOut(itoa(WinkelRPY[0], dbuff, 10));
		dBOut("P");
		dBOut(itoa(WinkelRPY[1], dbuff, 10));
		dBOut("Y");
		dBOut(itoa(WinkelRPY[2], dbuff, 10));
		dBOut("*\n");


		dBOut("##ROLL[0]:=");
		dBOut(itoa(getKaliprirtGyro()[0], dbuff, 10));
		dBOut("*PITCH[1]:=");
		dBOut(itoa(getKaliprirtGyro()[1], dbuff, 10));
		dBOut("*YAW[2]:=");
		dBOut(itoa(getKaliprirtGyro()[2], dbuff, 10));
		dBOut("*##\n");

	}
*/
}

int16_t *getWinkelRPY(){
	return WinkelRPY;
}
