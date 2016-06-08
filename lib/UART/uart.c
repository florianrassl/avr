/*
 * uart.c
 *
 *  Created on: Jul 7, 2014
 *      Author: florian
 */


#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <stdio.h>

#include "uart.h"

//#define USART0_BAUDRATE 9600
#define UBRR0_VALUE (((F_CPU / (USART0_BAUDRATE * 16UL))) - 1)

int uart0PutCharS(char byte, FILE *stream);

static FILE uart0Stdout = FDEV_SETUP_STREAM( uart0PutCharS, NULL, _FDEV_SETUP_WRITE );

void uart0Init(){
   UBRR0H = (uint8_t)(UBRR0_VALUE>>8);
   UBRR0L = (uint8_t)UBRR0_VALUE;

   UCSR0C = 3 << UCSZ00;
   UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
}

void uart0PutChar(uint8_t byte){
   while ((UCSR0A & _BV(UDRE0)) == 0);
   UDR0 = byte;
}

int uart0PutCharS(char byte, FILE *stream){
	if( byte == '\n' )
	        uart0PutCharS( '\r', stream );

	    uart0PutChar(byte);
	    return 0;
}

uint8_t uart0GetChar(){
   while( !(UCSR0A & (1<<RXC0)) );

   return(UDR0);
}

void uart0PutString(char *s){ //umschreiben auf ptr schreibweisse
	uint8_t i;
	for(i=0; i<strlen(s); i++){
		uart0PutChar(s[i]);
	}
}

/**
 * NOW you can use printf, etc.
 *
 */
void uart0SetStdout(){
	stdout = &uart0Stdout;
}

//#########################################################################################

#ifdef _AVR_IOMXX4_H_/* Only ATmega164P/324P/644P have a second USART. */
#if !defined(__AVR_ATmega644__)

//#define USART1_BAUDRATE 9600
#define UBRR1_VALUE (((F_CPU / (USART1_BAUDRATE * 16UL))) - 1)

int uart1PutCharS(char byte, FILE *stream);

static FILE uart1Stdout = FDEV_SETUP_STREAM( uart1PutCharS, NULL, _FDEV_SETUP_WRITE );

void uart1Init(){
   UBRR1H = (uint8_t)(UBRR1_VALUE>>8);
   UBRR1L = (uint8_t)UBRR1_VALUE;

   UCSR1C = 3 << UCSZ10;
   UCSR1B |= (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);
}

void uart1PutChar(uint8_t byte){
   while ((UCSR1A & _BV(UDRE1)) == 0);
   UDR1 = byte;
}

int uart1PutCharS(char byte, FILE *stream){
	if( byte == '\n' )
	        uart1PutCharS( '\r', stream );

	    uart1PutChar(byte);
	    return 0;
}

uint8_t uart1GetChar(){
   while( !(UCSR1A & (1<<RXC1)) );

   return(UDR1);
}

void uart1PutString(char *s){
	uint8_t i;
	for(i=0; i<strlen(s); i++){
		uart1PutChar(s[i]);
	}
}

/**
 * NOW you can use printf, etc.
 *
 */
void uart1SetStdout(){
	stdout = &uart1Stdout;
}
#endif
#endif
