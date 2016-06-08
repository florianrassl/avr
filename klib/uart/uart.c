/*
 * uart.c
 *
 *  Created on: Jul 7, 2014
 *      Author: florian
 */


#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "../include/charDev.h"

#ifndef USART0_BAUDRATE
#define USART0_BAUDRATE 9600
#endif

#define UBRR0_VALUE (((F_CPU / (USART0_BAUDRATE * 16UL))) - 1)

charDev uart0Dev;

void uart0Init(){
  UBRR0H = (uint8_t)(UBRR0_VALUE>>8);
  UBRR0L = (uint8_t)UBRR0_VALUE;
  UCSR0C = 3 << UCSZ00;
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);

  uart0Dev.putChar = &uart0PutChar;
  uart0Dev.getChar = &uart0GetChar;
  uart0Dev.rxChar = NULL;
}

void uart0PutChar(char byte){
  while ((UCSR0A & _BV(UDRE0)) == 0);
  UDR0 = byte;
}

char uart0GetChar(){
  while( !(UCSR0A & (1<<RXC0)) );
  return(UDR0);
}

ISR(USART_RX_vect){
  if(uart0Dev.rxChar != NULL)
    uart0Dev.rxChar(UDR0);
}


#ifdef _AVR_IOMXX4_H_/* Only ATmega164P/324P/644P have a second USART. */
#if !defined(__AVR_ATmega644__)

//#define USART1_BAUDRATE 9600
#define UBRR1_VALUE (((F_CPU / (USART1_BAUDRATE * 16UL))) - 1)

charDev uart1Dev;

void uart1Init(){
  UBRR1H = (uint8_t)(UBRR1_VALUE>>8);
  UBRR1L = (uint8_t)UBRR1_VALUE;
  UCSR1C = 3 << UCSZ10;
  UCSR1B |= (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);

  uart1Dev.putChar = &uart0PutChar;
  uart1Dev.getChar = &uart0GetChar;
  uart1Dev.rxChar = NULL;
}

void uart1PutChar(uint8_t byte){
  while ((UCSR1A & _BV(UDRE1)) == 0);
  UDR1 = byte;
}


uint8_t uart1GetChar(){
  while( !(UCSR1A & (1<<RXC1)) );
  return(UDR1);
}

ISR(USART1_RX_vect){
  if(uart1Dev.rxChar != NULL)
    uart1Dev.rxChar(UDR1);
}

#endif
#endif
