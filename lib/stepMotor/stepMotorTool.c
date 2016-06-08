#include "./stepMotor.h"
#include "../console/tool.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef F_CPU
#define F_CPU 1000000UL 
#endif

#include <util/delay.h>

void sleep(int t){
	while(t--)
		_delay_ms(1);
}

int8_t stepMotorTool(char *args[], uint8_t argc){	
	int8_t r;
	char d=R;
	int anz = 10;
	int sPause = 100;
	r=getArgNum(args, argc, "-h", 1);
	if(r>=0){
		fprintf(&toolOut, "smt -r/l -s anz \n\r");
		return 0;
	}
	r=getArgNum(args, argc, "-l", 1);
	if(r>=0)
		d=L;
	r=getArgNum(args, argc, "-s", 2);	
	if(r>=0)
		anz = atoi(args[r+1]);

	for(; anz; anz--){
		sMfullStep(d);
		sleep(sPause);
		fprintf(&toolOut, "step\n\r");
	}
	
	return 0;
}

