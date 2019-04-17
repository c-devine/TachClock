/*
 * .h
 *
 */

#ifndef FM_H_
#define FM_H_

#include "Arduino.h"

class FM {
public:
	FM(uint8_t pin, uint32_t period, uint32_t pulseWidth);
	void setPeriod(uint32_t period);
	void setPulseWidth(uint32_t pulseWidth);
	void process();
	virtual ~FM();

private:
	uint8_t _pin;
	uint32_t _period, _pulseWidth;
	bool _on;
	uint32_t _lastMicros;
};

#endif /* FM_H_ */
