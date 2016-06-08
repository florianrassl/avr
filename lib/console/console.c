//autor Florian Rassl

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "console.h"
#include "tool.h"

#define BUFFSICE 60
#define ARGS 8

void convertStrToArry(const char *strIn, const char* args[], uint8_t *argc);

static const char consoleBuff[BUFFSICE];
static const char* args[ARGS];
static uint8_t rxComplit=0;
static uint8_t argc;


//n.t.
toolRxChar *toolRxCharM;
//


void consoleInit(){
	toolGenericInit();
}

void consoleUpdate(){
	if(rxComplit){
		toolFlack = ALIVE;
		convertStrToArry(consoleBuff, (const char **)args, &argc);
		toolRxCharM = NULL;
		toolList((const char**)args, argc);
		rxComplit = 0;
	}
}

void convertStrToArry(const char *strIn, const char* args[], uint8_t *argc){
	char *strInPtr = (char*)strIn;
    char **strArgsPtr = (char**)args;
	(*argc)=0;
	if(strlen(strInPtr) == 0)
		return;
	if(*strInPtr!= ' ' && *strInPtr != '\r' && *strInPtr != '\n'){
		*strArgsPtr = strInPtr;
		strArgsPtr++;
		(*argc)++;
	}
	for(; *strInPtr != '\0'; strInPtr++){
		if(*strInPtr == ' '){
			*strInPtr = '\0';
            if(*(strInPtr+1) == ' ' || 
				*(strInPtr+1) == '\r' || 
					*(strInPtr+1) == '\n' || 
						*(strInPtr+1) == '\0')
                continue;
			(*argc)++;
			if((*argc) >= ARGS){
				(*argc) = 0;
				return;
			}
			*strArgsPtr = strInPtr+1;
            strArgsPtr++;
        }
    }
}

#define STRG '#' //STRG TASTE

inline char *consoleSetChar(char rxC){
	static char txS[6];
	static char *inBuffPtr = (char*)consoleBuff;
	static char oldRxC=0;

    if(oldRxC == STRG && rxC == 'c'){
        toolFlack = KILL;
		inBuffPtr = (char*)consoleBuff; 
		strcpy(txS, "^c\n\r");
        oldRxC = 0;
    }
	//wird beim laufenden tool ausgefürt   
	else if(rxComplit == 1){	
		if(toolRxCharM!=NULL)
			toolRxCharM(rxC);
		*txS='\0';
	}
	//zeilen umbruch d.h. tool wierd gestarted
	else if(rxC == '\r' || rxC == '\n' /*|| rxComplit == 1*/){ //n.c.
		*inBuffPtr = '\0';
		inBuffPtr = (char*)consoleBuff;
		rxComplit = 1;
		strcpy(txS, "\n\r");
	}
	//zeichen wird gelöscht
	else if(rxC == '\b' || rxC == 127){
		if(inBuffPtr > consoleBuff){
			inBuffPtr--;
			strcpy(txS, "\b \b");
			return txS;
		}
		strcpy(txS, "");
	}
	//buffer oferflow
	else if(inBuffPtr >= consoleBuff+BUFFSICE-2){
		strcpy(txS, "bof\n\r");
	}

	else if(oldRxC=='\t' && rxC == '\t'){
 		(*inBuffPtr)= '\0';
		autoErgTool(consoleBuff, BUFFSICE, &inBuffPtr);
		oldRxC='\0';
		*txS='\0';
    }
	//steuerzeichen entfärnen
	else if(rxC < 0x20){
		*txS='\0';
	}
	//zeichen wierd in buffer kopiert
	else{
		(*inBuffPtr)= rxC;
		inBuffPtr++;
		//
		txS[0] = rxC;
		txS[1] = '\0';
	}
	oldRxC = rxC;
	return txS;
}
