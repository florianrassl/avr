#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../klib/nsh/nsh.h"

#ifndef F_CPU
#define F_CPU 1000000UL 
#endif

#include <util/delay.h>



int8_t help(char *args[], uint8_t argc){ //bsp befehl ohne optionen
	(void)args;
	(void)argc;
	printf("help texst ..\n\r");
	return 0;
}

int8_t test(char *args[], uint8_t argc){ //bsp befehl mit option -help
	int8_t r;
	r=getArgNum(args, argc, "-help", 1);
	if(r>=0){
		printf("option \"-help\" wurde angefürt\n\r");
	}
	else{
		printf("es wurde keine option angefürt\n\r");
	}
	printf("hir gehts nach optionen teil weiter\n\r");
	_delay_ms(1);
	return 1;
}

#include "../../lib/nanoLed/nanoLed.h"

int8_t led(char *args[], uint8_t argc){
	int8_t r;
	r=getArgNum(args, argc, "-on", 1);
	if(r>=0){
		NANO_LED_ON();
		printf("LED ON\n\r");
		return 0;
	}
	r=getArgNum(args, argc, "-off", 1);
	if(r>=0){
		NANO_LED_OFF();
		printf("LED OFF\n\r");
		return 0;
	}
	printf("LED kein parameter übergeben!\n\r");
	printf("LED -on oder LED -off\n\r");
	return 0;
}

void toolInit(){
	addTool(&help, "help", NULL);
	addTool(&test, "test", NULL);
	addTool(&led, "led", NULL);

}
