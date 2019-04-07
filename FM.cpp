/*
 * Pwm.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: Chris
 */

#include "FM.h"

FM::FM(uint8_t pin, uint32_t period, uint32_t pulseWidth) {

	_pin = pin;
	_period = period;
	_pulseWidth = pulseWidth;
	_on = false;
	_lastMicros = 0;

	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

FM::~FM() {
	// TODO Auto-generated destructor stub
}

void FM::setPeriod(uint32_t period) {
	_period = period;
}

void FM::setPulseWidth(uint32_t pulseWidth) {
	_pulseWidth = pulseWidth;
}

void FM::process() {

	uint32_t delta = micros() - _lastMicros;

	if (!_on && delta >= _period) {
		digitalWrite(_pin, HIGH);
		_lastMicros = micros();
		_on = true;
		return;
	}
	if (_on && delta >= _pulseWidth) {
		digitalWrite(_pin, LOW);
		_lastMicros = micros();
		_on = false;
		return;
	}

}

