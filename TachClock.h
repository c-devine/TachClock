/*
 * TachCock.h
 *
 *  Created on: Jan 24, 2019
 *      Author: Chris
 */

#ifndef TACHCLOCK_H_
#define TACHCLOCK_H_

#include "Arduino.h"

#define LED_PIN 		13
#define BUTTON_PIN		4
#define TACH_PIN		5
#define SPEED_PIN		6
#define NEUTRAL_PIN		7

#define VERSION 1.0

void printTime();
uint32_t getButton();

#endif /* TACHCLOCK_H_ */
