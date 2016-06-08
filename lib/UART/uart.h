/*
 * uart.h
 *
 *  Created on: Jul 7, 2014
 *      Author: florian
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdio.h>

void uart0Init();
void uart0PutChar(uint8_t byte);
int uart0PutCharS(char byte, FILE *stream);
uint8_t uart0GetChar();
void uart0PutString(char *s);
void uart0SetStdout();


#ifdef _AVR_IOMXX4_H_
#if !defined(__AVR_ATmega644__)

void uart1Init();
void uart1PutChar(uint8_t byte);
int uart1PutCharS(char byte, FILE *stream);
uint8_t uart1GetChar();
void uart1PutString(char *s);
void uart1SetStdout();

#endif
#endif

#endif /* UART_H_ */
