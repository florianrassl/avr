//autor florian rassl

#include <stdint.h>

#include "../d-Bus/d-Bus.h"
#include "./adL.h"

int8_t *data;

void adLInit(){
	data = getDataPtr(0);
}

//bit 7 == add identikationsbit. bit 6 = msb fon data bit;

void rxChar(uint8_t c){
	static uint8_t add;
	if(c & (1<<7))
		add = c;
	else
		data[(add & 0x3f)] = c | ((add & 0x80)<<1);
}

char *adLSetChar(char c){
	static char r[2];
	rxChar(c);
	r[0]=c;
	r[1]='\0';	
	return r;
}

void txChar(txOut *out, uint8_t add, int8_t data){
	if(add>=64)
		return;
	out((add & 0x3f) | ((data>>1) & 0x40));	
	out(data & 0x7f);
}

void txInt16(txOut *out, uint8_t add, int16_t data){
	txChar(out, add, (int8_t)(data & 0xff));
	txChar(out, ++add, (int8_t)((data & 0xff00)>>8));
}

