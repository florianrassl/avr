/*
 * qControlCalc.h
 *
 *  Created on: 14.05.2014
 *      Author: florian
 */

#ifndef QCONTROLCALC_H_
#define QCONTROLCALC_H_

#include <stdint.h>

#define ROLL	0
#define PITCH	1
#define YAW		2

void init_qControl();
int16_t *getWinkelRPY();
void calcWinkel();

#endif /* QCONTROLCALC_H_ */
