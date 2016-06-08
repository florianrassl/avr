//autor Florian Rassl

#ifndef _NANOLED
#define _NANOLED 1

#include <avr/io.h>

#ifndef MCU
#define __AVR_ATmega328P__
#endif

#define NANO_LED_ON(){PORTB |= (1<<PB5);}
#define NANO_LED_OFF(){PORTB &= ~(1<<PB5);}

#endif /*_NANOLED*/
