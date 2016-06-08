/*
 * spi.h
 *
 *  Created on: 13.07.2013
 *      Author: florian
 */

#ifndef SPI_H_
#define SPI_H_

#define SPI_DDR DDRB
#define SPI_SCK 5
#define SPI_MOSI 3
#define SPI_MISO 4


uint8_t spiMasterInit(uint8_t interrupt, uint8_t msbfirst, uint8_t mod);
uint8_t spiSlaveInit(uint8_t interrupt, uint8_t msbfirst, uint8_t mod);

#endif /* SPI_H_ */
