
#include <stdio.h>
#include <avr/interrupt.h>

#define _MPU6050_TOOL

#include "../../lib/UART/uart.h"
#include "../../lib/console/console.h"
#include "../../lib/console/tool.h"
#include "../../lib/sensor/mpu6050.h"
#include "../../lib/twi_master/i2cmaster.h"


int main(){
	//char *ptr =(char*)getDataPtr(0);
	uart0Init();
	sei();
	uart0PutString("MPU\n\r");
	
	uart0SetStdout();	
	
	consoleInit();	
	i2c_init();

	addTool(&mpu6050Tool, "mpu");

	while(1){
		consoleUpdate();	
	}
	return 0;
}
