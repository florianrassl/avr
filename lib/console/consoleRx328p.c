//autor Florian Rassl

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../UART/uart.h"
#include "./console.h"

rxOut *out = &consoleSetChar;

ISR(USART_RX_vect){
	uart0PutString(out(UDR0));
}
