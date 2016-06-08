#include <stdio.h>
#include <avr/interrupt.h>


#include "../../lib/UART/uart.h"
#include "../../lib/console/console.h"
#include "../../lib/stepMotor/stepMotor.h"
#include "../../lib/stepMotor/stepMotorTool.h"

void init(){
	uart0Init();
    sei();
    uart0PutString("gerald test\n\r");
	consoleInit();
	addTool(&stepMotorTool, "stm", NULL);
	sMenabel();
}

void loop(){
	consoleUpdate();

}


int main(){

	init();
	while(1)loop();


	return 0;
}
