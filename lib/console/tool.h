//autor Florian Rassl
#ifndef _TOOL
#define _TOOL 1

#include <stdint.h>

#include <stdio.h>
/*
static FILE toolOut = FDEV_SETUP_STREAM( uart0PutCharS, NULL, _FDEV_SETUP_WRITE );
static FILE toolIn = FDEV_SETUP_STREAM( uart0PutCharS, NULL, _FDEV_SETUP_WRITE );
*/

#include "../UART/uart.h"

extern void toolGenericInit();
extern void toolPrintPrompt();
extern void toolList(const char* args[], const uint8_t  argc);
extern int getArgNum(char* argv[], int argc, char arg[], int args);

typedef int8_t toolMethode(char *args[], uint8_t argc);
typedef void toolRxChar(char c);

extern void addTool(toolMethode *toolMethode, char* toolName, toolRxChar toolMethodeRxChar);
extern void autoErgTool(const char *buff, uint8_t buffSice, char **buffPtr);

extern FILE toolOut;

extern char toolFlack;
enum toolFlacks{
	ALIVE, KILL, PAUS
};
//extern FILE toolOut = FDEV_SETUP_STREAM( uart0PutCharS, NULL, _FDEV_SETUP_WRITE );

#endif /*_TOOL*/
