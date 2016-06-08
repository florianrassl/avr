/*
 * adc.c
 *
 *  Created on: Jul 22, 2014
 *      Author: florian
 */

#include <avr/io.h>
#include <stdint.h>

void initADC(){
	ADMUX |= (1<<REFS0); //externe ReferenzSpanung wen REFS0/1 =0 dan interne REFSpamung
	//ADMUX |= (1<<ADLAR); // 8 Hbit in ADCH
	ADCSRA |=(1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);


}

uint16_t getADCData(const uint8_t pin){
	//(void)ADC;

	if(pin>=15){
		return -1;
	}

	ADMUX = ((0xf0 & ADMUX) | pin);
	ADCSRA|=(1<<ADSC);
	while(ADCSRA & (1<<ADSC));

	return ADC;
}
