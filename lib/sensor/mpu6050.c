
#include <stdint.h>
#include <string.h>
#include <util/delay.h>
#include "../twi_master/i2cmaster.h"
#include "../twi_master/twiBase.h"
#include "mpu6050.h"


#define MPUI2CADD 0xD0 //0b1101000 //AD0 = 0
//#define MPUi2CADD 0xD2 //0b1101001 //AD0 = 1

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C

#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

void sleep(uint16_t n);

void mpu6050Init(uint16_t gyroScale, uint8_t accelScale){
	writeRegister(MPUI2CADD, PWR_MGMT_1, 0);
	writeRegister(MPUI2CADD, PWR_MGMT_2, 0);
	
	writeRegister(MPUI2CADD, GYRO_CONFIG, (7<<5));
	writeRegister(MPUI2CADD, ACCEL_CONFIG, (7<<5));
	
	switch(gyroScale){
		case 500:
        writeRegister(MPUI2CADD, GYRO_CONFIG, (1<<3));
		break;
		case 1000:
        writeRegister(MPUI2CADD, GYRO_CONFIG, (2<<3));
		break;
		case 2000:
        writeRegister(MPUI2CADD, GYRO_CONFIG, (3<<3));
		break;
		case 250:
		default:
		writeRegister(MPUI2CADD, GYRO_CONFIG, 0);
	}
	switch(accelScale){
		case 4:
		writeRegister(MPUI2CADD, GYRO_CONFIG, (1<<3));
		break;
		case 8:
		writeRegister(MPUI2CADD, GYRO_CONFIG, (2<<3));
		break;
		case 16:
		writeRegister(MPUI2CADD, GYRO_CONFIG, (3<<3));
		break;
		case 2:
		default:
		writeRegister(MPUI2CADD, GYRO_CONFIG, 0);
	}
	sleep(100);
}

void readBlock(uint8_t reg, int16_t *data){
	i2c_start(MPUI2CADD+I2C_WRITE);
	i2c_write(reg); // register to read
    i2c_rep_start(MPUI2CADD+I2C_READ); // read a byte
	
	*data = (i2c_readAck()<<8);
	*data |= (i2c_readAck());
	data++;
    *data = (i2c_readAck()<<8);
	*data |= i2c_readAck();
	data++;
	*data = (i2c_readAck()<<8);
	*data |= i2c_readNak();
    i2c_stop();

}

void mpu6050GetACCEL(int16_t *data){
	readBlock(ACCEL_XOUT_H, data);
}

void mpu6050GetGYRO(int16_t *data){
	readBlock(GYRO_XOUT_H, data);
}

void memadd(int16_t *de, int16_t *dd, uint8_t n){while(n--)de[n]+=dd[n];}
void memsub(int16_t *de, int16_t *dd, uint8_t n){while(n--)de[n]-=dd[n];}
void memdev(int16_t *de, int16_t dd, uint8_t n){while(n--)de[n]/=dd;}
void memrsh(int16_t *de, int8_t rsh, uint8_t n){while(n--)de[n]>>=rsh;}
void sleep(uint16_t n){while(n--)_delay_ms(1);}

void mpu6050Cal(int16_t *gOfSet, int16_t *aOfSet, uint8_t ofCount){
	int16_t data[3];
	int i = ofCount;
	memset(gOfSet, 0, 3);
	memset(aOfSet, 0, 3);
	while(i--){
		sleep(50);
		mpu6050GetGYRO(data);
		memadd(gOfSet, data, 3);
		mpu6050GetACCEL(data);
		memadd(aOfSet, data, 3);
	}
	memdev(gOfSet, ofCount, 3);
	memdev(aOfSet, ofCount, 3);
}

void mpu6050GetACCELCal(int16_t *data, int16_t *ofSet, uint8_t rsh){
	mpu6050GetACCEL(data);
	memsub(data, ofSet, 3);
	memrsh(data, rsh, 3);
}

void mpu6050GetGYROCal(int16_t *data, int16_t *ofSet, uint8_t rsh){
	mpu6050GetGYRO(data);
	memsub(data, ofSet, 3);
	memrsh(data, rsh, 3);
}


#ifdef _MPU6050_TOOL

#include <stdio.h>
#include <stdlib.h>
#include "../console/tool.h"

#define AS 6
#define GS 4

int16_t ofSet[6];

void print(){
	static int16_t data[6];
	mpu6050GetGYROCal(data, ofSet, GS);
    mpu6050GetACCELCal(data+3, ofSet+3, AS);
	//printf("GYRO :X=%d, Y=%d, Z=%d\n\r", data[0],	data[1],	data[2]);
   	printf("ACCEL:X=%d, Y=%d, Z=%d\n\r", data[3],	data[4],	data[5]);
}

void mpu6050Tool(char *args[], uint8_t argc){
	int8_t r;
    r=getArgNum(args, argc, "-help", 1); 
    if(r>=0){
		printf("mpu -init gyroScale accelScale\n\r");
		printf("mpu -print (anz rtime)\n\r");
		return;
    } 
	r=getArgNum(args, argc, "-init", 1);
	if(r>=0){
		if(argc == 3)
			mpu6050Init(atoi(args[r+1]), atoi(args[r+2]));
		else
			mpu6050Init(0,0); //default init
		mpu6050Cal(ofSet, ofSet+3, 10);
		return;
	}
	r=getArgNum(args, argc, "-print", 1);
	if(r>=0){
		if(argc>=3){
			uint16_t i;
			for(i=atoi(args[r+1]);i; i--){
				print();
				sleep(atoi(args[r+2]));
			}
		}
		else{
			print();
		}
		return;
	}
	printf("??\n\r");
}
#endif
