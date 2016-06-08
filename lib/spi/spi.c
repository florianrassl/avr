/*
 * spi.c
 *
 *  Created on: 13.07.2013
 *      Author: florian
 */

//#include <avr/iom328p.h>
#include <avr/io.h>
#include "spi.h"

static uint8_t modus(unsigned char mod);
/*
uint8_t spiMasterInit(uint8_t interrupt, uint8_t msbfirst, uint8_t mod){ //Master nicht vrtic implementiret siche tabelu unten

	SPI_DDR |= (1<<SPI_SCK) | (1<<SPI_MOSI) | (0<<SPI_MISO);

	SPCR = 0x00;

	SPCR |= (1<<SPE) | (1<<MSTR);

	if(interrupt)
		SPCR |= (1<<SPIE);

	if(!msbfirst)
		SPCR |= (1<<DORD);

	//modus
		if(modus(mod))
			return 1;

	return 0;
}
*/

uint8_t spiSlaveInit(uint8_t interrupt, uint8_t msbfirst, uint8_t mod){

	SPI_DDR |= (0<<SPI_SCK) | (0<<SPI_MOSI) | (1<<SPI_MISO);

	SPCR = 0x00;

	SPCR |= (1<<SPE);

	if(interrupt)
		SPCR |= (1<<SPIE);

	if(msbfirst==0)
		SPCR |= (1<<DORD);

	//modus
	if(modus(mod))
		return 1;

	return 0;
}

static uint8_t modus(unsigned char mod){
	switch(mod){
	case 0:
		break;
	case 1:
		SPCR |= (1<<CPHA);
		break;
	case 2:
		SPCR |= (1<<CPOL);
		break;
	case 3:
		SPCR |= (1<<CPHA) | (1<<CPOL);
		break;
	default:
		return 1;
		break;
	}
	return 0;
}


/*
SPI2X 	SPR1 	SPR0 	SCK Frequenz
0 		0 		0 		fOSC/4
0 		0 		1	 	fOSC/16
0 		1 		0	 	fOSC/64
0 		1 		1 		fOSC/128
1 		0 		0 		fOSC/2
1 		0 		1 		fOSC/8
1 		1	 	0 		fOSC/32
1 		1 		1 		fOSC/64
 */


