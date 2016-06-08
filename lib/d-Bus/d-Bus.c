//autor Florian Rassl

#include <stdint.h>
#ifdef DEBUG
#include <stdio.h>
#endif

#include "d-Bus.h"

#ifndef NULL
#define NULL 0
#endif

int8_t dBusData[DBUSSIZE];

int8_t *getDBusPtr(uint8_t add){
	if(add > DBUSSIZE){
		#ifdef DEBUG
		printf("ERROR!! d-Bus\n\r");
		#endif
		return NULL;	
	}
	return &dBusData[add];
}

#ifdef _CONSOLE
#include "../console/console.h"
#endif

#ifdef _RXB8
#include "../console/console.h"
#include "../RXB8/pars.h"
#endif

#ifdef _ADL
#include "../console/console.h"
#include "../adL/adL.h"
#endif


#define _D_BUS_TOOL

#ifdef _D_BUS_TOOL //noch nicht getestet
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../console/tool.h"

void d_busTool(char *args[], uint8_t argc){
	int8_t r;
	//int8_t *dBusPtr = getDataPtr(0);
	r=getArgNum(args, argc, "-help", 1);
	if(r>=0){
		printf("-print 8/16 ###default = 16\n\r");
		printf("-set8 add data\n\r");
		printf("-set16 add data\n\r");
		return;
	}
	r=getArgNum(args, argc, "-print", 2);
	if(r>=0){
		if(strcmp(args[r+1], "8")==0){
			for(r=0; r<DBUSSIZE; r++){
				printf("add %d: data %d\n\r", r, (int8_t)dBusData[r]);
			}
		}
		else{
			for(r=0; r<DBUSSIZE/2; r++){
				printf("add %d: data %d\n\r", r, (int16_t)((int16_t*)dBusData)[r]);
			}
		}
		return;
	}

	r=getArgNum(args, argc, "-set8", 3);
	if(r>=0){
		uint8_t add = atoi(args[r+1]);
		if(add > DBUSSIZE){
			printf("PARS ERROR\r\n");
			return;
		}
		dBusData[add] = (int8_t)atoi(args[r+2]);
		return;	
	}
	r=getArgNum(args, argc, "-set16", 3);
	if(r>=0){
		uint8_t add = atoi(args[r+1]);
		if(add > DBUSSIZE/2-1){
			printf("PARS ERROR\r\n");
			return;
		}
		((int16_t*)dBusData)[add] = (int16_t)atoi(args[r+2]);
		return;
	}
	printf("kein parameter:: d-bus -help ???\n\r");
}
#endif

void dBusUpdate(){
	#ifdef _CONSOLE
	if(data[PARSADD]==PARSMETHCONSOLE)
		out = &consoleSetChar;	
	else 
	#endif
	#ifdef _ADL
	if(data[PARSADD]== PARSMETHADL)
		out = &adLSetChar;
	else
	#endif
	#ifdef _RXB8
	if(data[PARSADD] == PARSMETHRXB8)
		out = &parsSetChar;
	#endif
	;//die lehre anweisung muss da stehen!!
}
