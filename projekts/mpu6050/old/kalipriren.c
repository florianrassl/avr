/*
 * etc.c
 *
 *  Created on: 15.05.2014
 *      Author: florian
 */
#include <stdint.h>
#include <util/delay.h>

#include "./kalipriren.h"
#include "./qLage.h"
#include "./../sensor/gyro.h"
#include "./../sensor/adxl345.h"
#include "./../main/main.h"
#include "./../spi_address_logic/dBridge.h"
#include "./../spi_address_logic/spi_address_logic.h"
#include "./../spi_address_logic/regMap.h"



#define kBuffSize 10
//methoden müssen mindesten kBuffSize aufgeruffen werden um werte zu erhalten

int16_t kGyro[3]={0,0,0};
//int16_t ofset[3]={0,0,0};
int16_t kAdxl[3]={0,0,0};

struct rund{
	uint8_t dataPointer;
	int16_t out;
	int16_t buff[kBuffSize];
};

struct rund adxl[3]={{0,0},{0,0},{0,0}}, gyro[3]={{0,0},{0,0},{0,0}};

void Rund(struct rund *rd, int16_t bp){
	uint8_t i;
	(*rd).out=0;
	if((*rd).dataPointer>=kBuffSize)
		(*rd).dataPointer=0;
	(*rd).buff[(*rd).dataPointer]=bp;
	for(i=0; i<kBuffSize; i++)
		(*rd).out+=(*rd).buff[i];
	(*rd).out=(*rd).out/kBuffSize;
	(*rd).dataPointer++;
}

void kaliprire(){
	uint8_t i;
	for(i=0; i<kBuffSize; i++){
		_delay_ms(500);
		//adxlRefresh();
		gyroRefresh();

		//Rund(&adxl[AX], getAdxlData()[AX]);
		//Rund(&adxl[AY], getAdxlData()[AY]);
		//Rund(&adxl[AZ], getAdxlData()[AZ]);

		Rund(&gyro[GX], getGyroData()[GX]);
		Rund(&gyro[GY], getGyroData()[GY]);
		Rund(&gyro[GZ], getGyroData()[GY]);

	}
	getWinkelRPY()[0]=0;
	getWinkelRPY()[1]=0;
	getWinkelRPY()[2]=0;
	address[LED] = 80;
}

int16_t *getKaliprirtGyro(){
	uint8_t i;
	for(i=0; i<3; i++){
		kGyro[i] = (getGyroData()[i])-(gyro[i]).out;
		//kGyro[i] = (getGyroData()[i])/50-ofset[i];
	}
	return kGyro;
}

int16_t *getKaliprirtAdxl(){
	uint8_t i;
	for(i=0; i<3; i++){
		kAdxl[i] = getAdxlData()[i]-(adxl[i]).out;
	}
	return kAdxl;
}
