/*
 * adc.h
 *
 *  Created on: Jul 22, 2014
 *      Author: florian
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void initADC();
uint16_t getADCData(const uint8_t pin);

#endif /* ADC_H_ */
