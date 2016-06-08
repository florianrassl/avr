//autor Florian Rassl
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "tool.h"
#include "console.h"

#ifndef MCU
#define __AVR_ATmega328P__ 1
#endif

FILE toolOut = FDEV_SETUP_STREAM( uart0PutCharS, NULL, _FDEV_SETUP_WRITE );



typedef struct tool{
	char *toolName;
	toolMethode *toolMethode;
	toolRxChar *toolMethodeRxChar;
}tool;

#ifndef TOOLSSIZE
#define TOOLSSIZE 10
#endif

static uint8_t toolCount;
static tool tools[TOOLSSIZE];

char toolFlack;

static int8_t clearTool(char *args[], uint8_t argc){ // selbsterklärend
	(void)args;
	(void)argc;
	fprintf(&toolOut, "\x1B[2J\x1B[H");
	return 0;
}

static int8_t printTool(char *args[], uint8_t argc){//gibt alle tools aus
	(void)args;
	(void)argc;
	uint8_t i;
	fprintf(&toolOut, "comandos:\n\r");
	for(i=0; i<toolCount; i++){
		fprintf(&toolOut, "%s\n\r", tools[i].toolName);
	}	
	return 0;
}

#define _PORT_TOOL
#ifdef _PORT_TOOL

#include <avr/io.h>

static int8_t portTool(char *args[], uint8_t argc){
	int8_t r;
	r=getArgNum(args, argc, "-h", 1);
	if(r>=0){
		fprintf(&toolOut, "port -'b/c/d' \"value\"\n\r");
	}
	r=getArgNum(args, argc, "-b", 2);
	if(r>=0){
		PORTB = (int8_t)atoi(args[1]);
	}
	r=getArgNum(args, argc, "-c", 2);
	if(r>=0){
		PORTC = (int8_t)atoi(args[1]);
	}
	r=getArgNum(args, argc, "-d", 2);
	if(r>=0){
		PORTD = (int8_t)atoi(args[1]);
	}
	return 0;
}
#endif

void toolGenericInit(){ // selbsterklären
	toolCount=0;
	addTool(&clearTool, "clear", NULL);
	addTool(&printTool, "print", NULL);
	#ifdef _PORT_TOOL
	addTool(&portTool, "port", NULL);
	#endif
	toolPrintPrompt();
}

void addTool(toolMethode *toolMethode, char* toolName, toolRxChar toolMethodeRxChar){ //fürt ein tool hinzu
	if(toolCount > TOOLSSIZE){
		fprintf(&toolOut, "TOOLLIST OFERFLOW\n\r");
		return;
	}
	tools[toolCount].toolName = toolName;
	tools[toolCount].toolMethode = toolMethode;
	tools[toolCount].toolMethodeRxChar =toolMethodeRxChar;
	toolCount++;
}

void toolList(const char *args[], uint8_t argc){ //sucht tool in liste.
	char** argsPtr = (char**)args;
	uint8_t i;
	if(argc>0){
		for(i=0; i<toolCount; i++){
			if(!strcmp(args[0], tools[i].toolName)){
				toolRxCharM = tools[i].toolMethodeRxChar;
				while(tools[i].toolMethode(&argsPtr[1], argc-1) && toolFlack!=KILL);
				break;
			}
		}
		if(i==toolCount){
			fprintf(&toolOut, "%s: command not found\n\r", args[0]);
		}
	}
	toolPrintPrompt();
}

void toolPrintPrompt(){ // gibt promt aus.
	fprintf(&toolOut, "AVR# ");
}

void autoErgTool(const char *buff, uint8_t buffSice, char **buffPtr){ //sucht nach argg0 und ergänzst dises 
	uint8_t i;
	uint8_t n=0, t=0;

	for(i=0; i<toolCount; i++){
		if(!strncmp(buff, tools[i].toolName, strlen(buff))){
			n++;
			t=i;
		}
	}

	for(i=0; i<toolCount; i++){
		if(!strncmp(buff, tools[i].toolName, strlen(buff))){
			if(n>1){
				fprintf(&toolOut,"\r\n");
				fprintf(&toolOut, "%s\t", tools[i].toolName);
			}
		}
	}
	if(n){
		if(n==1){
			strncpy((char*)buff, tools[t].toolName, buffSice-2);
			fprintf(&toolOut,"%s", *buffPtr);
			*buffPtr=(char*)buff+strlen(buff);
		}
		else{
			fprintf(&toolOut,"\n\r");
			toolPrintPrompt();
			fprintf(&toolOut,"%s", buff);
		}
	}
}

int getArgNum(char* argv[], int argc, char arg[], int args){ //sucht nach arg in arg List
	int i;
	for(i=0; i<argc; i++){
		if((i+args)>=argc+1)
			return -1;
		if(strncmp(argv[i], arg, strlen(arg))==0){
			return i;
		}
	}
	return -1;
}

