/*
 * uart.h
 *
 *  Created on: Jul 7, 2014
 *      Author: florian
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "../include/charDev.h"

extern charDev uart0Dev;

void uart0Init();
void uart0PutChar(char byte);
char uart0GetChar();

#ifdef _AVR_IOMXX4_H_
#if !defined(__AVR_ATmega644__)

extern charDev uart1Dev;

void uart1Init();
void uart1PutChar(char byte);
char uart1GetChar();

#endif
#endif

#endif /* UART_H_ */
