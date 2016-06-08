#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../../lib/nanoLed/nanoLed.h"
#include "../../lib/ADC/adc.h"
#include "../../lib/UART/uart.h"


//#define _DEBUG
#define _KILLTIME 0x4000
#define INTBLOCK 200

void initTimer(void){
	OCR1A = _KILLTIME;
	TCCR1B |= (1 << WGM12);// Mode 4, CTC on OCR1A
	TIMSK1 |= (1 << OCIE1A);//Set interrupt on compare match
	TCCR1B |= (1 << CS12) | (1 << CS10);// set prescaler to 256 and start the timer
}

void initExInterrups(){
	EICRA |= (1 << ISC11) | (1 << ISC01); 
	EIMSK |= (1 << INT1);		//interrups enaibeld
	EIMSK |= (1 << INT0);
}


void init(){

	DDRB=0xff;
	PORTD=0x00;
	
	#ifdef _DEBUG	
	uart0Init();
	uart0SetStdout();		
	#endif

	initADC();
	initTimer();
	initExInterrups();
	DDRD=0x00;
	PORTD=0x00;

	
}

volatile uint16_t count=0;
volatile uint8_t l=0, r=0;

void loop(){
	static uint16_t poti;
	
	poti = getADCData(1)/7;
	#ifdef _DEBUG
	printf("count:%d\t##ADC:%d\t##L%d\t##R%d\n\r", count, poti, l, r);
	#endif
	if((l^r) && (poti<=count)){
		NANO_LED_ON();
		PORTB |= (1 << PB4);
	}
	else{
		NANO_LED_OFF();
		PORTB &= ~(1 << PB4);
	}
}

int main(){
	_delay_ms(5);
	init();
	sei();
	while (1) loop();
	return 0;
}

ISR(TIMER1_COMPA_vect){
	l=0;
	r=0;
	count=0;
}

ISR(INT0_vect){
	EIMSK &= ~(1 << INT0);
	EIFR &= ~(1 << INTF0);
	_delay_ms(INTBLOCK);
	if(!(EIFR & (1 << INTF0)))
		count++;
	l=1;
	TCNT1=0x0000;
	EIFR &= ~(1 << INTF0);
	EIMSK |= (1 << INT0);
}

ISR(INT1_vect){
	EIMSK &= ~(1 << INT1);
	EIFR &= ~(1 << INTF1);
	_delay_ms(INTBLOCK);
	if(!(EIFR & (1 << INTF1)))
		count++;
	r=1;
	TCNT1=0x0000;
	EIFR &= ~(1 << INTF1);
	EIMSK |= (1 << INT1);
}
