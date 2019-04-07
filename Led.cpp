#include "Led.h"
#include "math.h"

Led::Led(uint8_t pin) {
	_on = false;
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

Led::~Led() {

}

void Led::toggle() {
	if (_on) {
		off();
	} else {
		on();
	}
}

void Led::on() {
	digitalWrite(_pin, LOW);
	_on = true;
}

void Led::off() {
	digitalWrite(_pin, HIGH);
	_on = false;
}

void Led::flash(uint16_t count, uint32_t delayMs) {

	for (uint32_t i = 0; i< count; i++)
	{
		on();
		delay(delayMs);
		off();
		delay(delayMs);
	}
}

