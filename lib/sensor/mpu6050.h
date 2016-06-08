//autor florian rassl

#ifndef _MPU6050
#define _MPU6050 1
#include <stdint.h>

#define GX 1
#define GY 2
#define GZ 3

#define AX 1
#define AY 2
#define AZ 3

extern void mpu6050Init(uint16_t gyroScale, uint8_t accelScale);
extern void mpu6050GetACCEL(int16_t *data);
extern void mpu6050GetGYRO(int16_t *data);
#define _MPU6050_TOOL
#ifdef _MPU6050_TOOL
extern void mpu6050Tool(char *args[], uint8_t argc);
#endif
#endif /*_MPU6050*/
