/*
 * pars.c
 *
 *  Created on: Jul 6, 2014
 *      Author: florian
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../console/console.h"

#define BUFFSIZE 20
#define PARSBUFF 7

//int16_t *pData;

volatile char uBuff[BUFFSIZE];
volatile uint8_t buffPtr = 0;


/*
 * e	 	==> 0
 * a		==> 1
 * p||n		==> 2
 * 0-9		==> 3
 * c		==> 4#
 * \0		==> 5
 *
 * ###########################
 * cccaADDp/nDATAeeeee
 * ###########################
 */

#include "../d-Bus/d-Bus.h"
int16_t *pData;
void parsInit(){
	pData = (int16_t*)getDataPtr(0)-PARSADD;
}

uint8_t testUPars(char *s, int8_t index, uint8_t zAlt, char *pBuff, uint8_t bP, int16_t data, uint8_t add){
	index--;

	if(index<0){
		return 0;
	}

	if(s[index] == '\0' && zAlt == 5){
		return testUPars(s, index, 5, pBuff, bP, data, add);
	}
	else if(s[index]=='e' && (zAlt == 0 || zAlt == 5)){
		bP=PARSBUFF-2;
		memset(pBuff, '0', PARSBUFF);
		pBuff[PARSBUFF-1]='\0';
		return testUPars(s, index, 0, pBuff, bP, data, add);
	}
	else if((s[index]>47 && s[index]<58) && (zAlt==0 || zAlt==2 || zAlt == 3)){
		pBuff[bP] = s[index];
		bP--;
		if(bP<0){
#ifdef DEBUG
			uartPutString("\n-1 PARS ERROR pBuff OVERFLOW\n");
#endif
			return -1;
		}
		return testUPars(s, index, 3, pBuff, bP, data, add);
	}
	else if(s[index]=='a' && zAlt==3){
		add = atoi(pBuff);
		if(add>=16){
#ifdef DEBUG
			uartPutString("\n-1 PARS ERROR ADD OVERVLOW\n");
#endif
			return -1;
		}
		pData[add] = data;
		bP=PARSBUFF-2;
		memset(pBuff, '0', PARSBUFF);
		pBuff[PARSBUFF-1]='\0';
		return testUPars(s, index, 1, pBuff, bP, data, add);
	}
	else if((s[index]=='p' || s[index]=='n') && zAlt == 3 ){
		data = atoi(pBuff);
		if(s[index]=='n'){
			data*=-1;
		}
		bP=PARSBUFF-2;
		memset(pBuff, '0', PARSBUFF);
		pBuff[PARSBUFF-1]='\0';
		return testUPars(s, index, 2, pBuff, bP, data, add);
	}
	else if(s[index]=='c' && (zAlt==1 || zAlt==4)){
		return testUPars(s, index, 4, pBuff, bP, data, add);
	}
#ifdef DEBUG
	uartPutString("\n-1 PARS ERROR SYNTAX\n");
#endif
	return -1;
}

int8_t parsBuff(){
	if(!*pData){
		out = &consoleSetChar;
	}
	char pBuff[PARSBUFF];
	uint8_t bP=PARSBUFF-2;
	uint8_t add=0;
	int16_t data=0;
	memset(pBuff, '0', PARSBUFF);
	pBuff[PARSBUFF-1]='\0';
	return testUPars((char*)uBuff, BUFFSIZE, 5, pBuff, bP, data, add);
}

void clearBuff(){
#ifdef DEBUG
	uartPutString((char*)uBuff);
#endif
	memset((char*)uBuff, '\0', BUFFSIZE);
#ifdef DEBUG
	uartPutString("\nclear\n");
	uartPutString((char*)uBuff);
#endif
}

char *parsSetChar(char c){
	static char r[2];
	r[0]=c;
	r[1]='\0';
	if(c == 'c'){
		clearBuff();
		buffPtr=0;
	}
	else if(buffPtr <BUFFSIZE){
		uBuff[buffPtr] = c;
		buffPtr++;
	}
	return r;
}
