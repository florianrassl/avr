/*
 * pars.h
 *
 *  Created on: Jul 7, 2014
 *      Author: florian
 */

#ifndef PARS_H_
#define PARS_H_

#include <stdint.h>

int8_t parsBuff();
char *parsSetChar(char c);
#ifdef _D_BUS
void parsInit();
#else
extern int16_t pData[16];
#endif
#endif /* PARS_H_ */
