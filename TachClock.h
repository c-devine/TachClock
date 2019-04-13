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
#define BUTTON_PIN		12
#define BUTTON_GND		11
#define TACH_PIN		5
#define SPEED_PIN		6
#define NEUTRAL_PIN		7
#define FUEL_PINS		{A0,A1,A2,A3}

#define VERSION 1.0

void printTime();
bool processButton();
uint32_t getButton();
void setFuel(uint8_t minutes);

#endif /* TACHCLOCK_H_ */
