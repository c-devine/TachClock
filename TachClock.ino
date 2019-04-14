#include "TachClock.h"
#include <RTClib.h>
#include "FM.h"
#include "Led.h"

Led led(LED_PIN);
FM tach(TACH_PIN, 6000, 500);
FM speed(SPEED_PIN, 33333, 150);
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday" };

uint32_t hourLows[] = { 300000, 61000, 31000, 20000, 14600, 11600, 9500, 7950,
		6900, 6100, 5400, 4850, 4500 };
uint8_t fuelPins[] = FUEL_PINS;

void setup() {

	Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(BUTTON_GND, OUTPUT);
	digitalWrite(BUTTON_GND, LOW);
	pinMode(NEUTRAL_PIN, INPUT);

	// set up the fuel pins
	for (uint8_t i = 0; i < 4; i++) {
		pinMode(fuelPins[i], INPUT);
	}

	led.on();

	Serial.println("Starting RTC");

	if (!rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (true)
			;
	}

	if (!rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
		// This line sets the RTC with an explicit date & time, for example to set
		// January 21, 2014 at 3am you would call:
		// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
	}

	printTime();
}

void loop() {

	static bool buttonPressed = false;
	static uint32_t lastMillis = 0;
	static uint32_t rpmPeriod = 10000;
	static uint32_t minutePeriod = 33333;
	uint32_t currentMillis = millis();

	if (buttonPressed || (currentMillis - lastMillis > 1000)) {
		buttonPressed = false;
		led.toggle();
		lastMillis = currentMillis;
		DateTime now = rtc.now();
		uint8_t hour = now.hour();
		uint8_t minute = now.minute();
		uint8_t second = now.second();

		if (hour >= 12) {
			pinMode(NEUTRAL_PIN, OUTPUT);
			digitalWrite(NEUTRAL_PIN, LOW);
		} else {
			pinMode(NEUTRAL_PIN, INPUT);
		}

		float hourFrac = ((minute * 60 + second) / 3600.0);
		int index = hour < 12 ? hour : hour - 12;

		rpmPeriod = hourLows[index]
				- ((hourLows[index] - hourLows[index + 1]) * hourFrac);

		tach.setPeriod(rpmPeriod);

		if (minute == 0)
			minutePeriod = 2500000;
		else if (minute == 1)
			minutePeriod = 1500000;
		else
			minutePeriod = 1000000.0 / ((float) minute * .46);

		speed.setPeriod(minutePeriod);

		setFuel(minute);
	}

	tach.process();
	speed.process();
	buttonPressed = processButton();
}

void setFuel(uint8_t minutes) {

	static uint8_t lastQuarter = 5;
	uint8_t quarter;

	if (minutes < 14 || minutes > 58)
		quarter = 0;
	else if (minutes < 29)
		quarter = 1;
	else if (minutes < 44)
		quarter = 2;
	else
		quarter = 3;

	if (quarter != lastQuarter) {
		lastQuarter = quarter;

		for (uint8_t i = 0; i < 4; i++) {
			if (quarter == i) {
				digitalWrite(fuelPins[i], LOW);
				pinMode(fuelPins[i], OUTPUT);
			} else
				pinMode(fuelPins[i], INPUT);
		}
	}
}

bool processButton() {

	uint32_t buttonMs = getButton();
	// check for no status, and return right away
	if (buttonMs == 0)
		return false;

	DateTime now = rtc.now();
	uint8_t minute = now.minute();
	uint8_t hour = now.hour();

	// < .5 second is an update to minutes
	if (buttonMs < 500) {
		if (minute == 59)
			minute = 0;
		else
			minute++;
	} else {
		if (hour == 23)
			hour = 0;
		else
			hour++;
	}

	rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour, minute, 0));
	return true;

}

uint32_t getButton() {

	static bool buttonPressed = false;
	static uint32_t buttonPressedMillis = 0;

	if (!buttonPressed && digitalRead(BUTTON_PIN) == LOW) {
		buttonPressed = true;
		buttonPressedMillis = millis();
		return 0;
	}

	if (buttonPressed && digitalRead(BUTTON_PIN) == HIGH) {
		buttonPressed = false;
		return millis() - buttonPressedMillis;
	}

	return 0;
}

void printTime() {

	DateTime now = rtc.now();

	Serial.print(now.year(), DEC);
	Serial.print('/');
	Serial.print(now.month(), DEC);
	Serial.print('/');
	Serial.print(now.day(), DEC);
	Serial.print(" (");
	Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
	Serial.print(") ");
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();
}
