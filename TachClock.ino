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

uint32_t hourLows[] = { 61000, 31000, 20000, 14600, 11600, 9500, 7950, 6900,
		6100, 5400, 4850, 4500 };

//The setup function is called once at startup of the sketch
void setup() {

	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(NEUTRAL_PIN, INPUT);

	led.on();
	Serial.begin(9600);

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

// The loop function is called in an endless loop
void loop() {

	static uint32_t lastMillis = 0;
	uint32_t currentMillis = millis();
	static uint32_t rpmPeriod = 10000;
	static uint32_t minutePeriod = 33333;

	if (currentMillis - lastMillis > 1000) {
		led.toggle();
		lastMillis = currentMillis;
		DateTime now = rtc.now();

		if (now.hour() >= 12) {
			pinMode(NEUTRAL_PIN, OUTPUT);
			digitalWrite(NEUTRAL_PIN, LOW);
		}
		else
		{
			pinMode(NEUTRAL_PIN, INPUT);
		}

		float hourFrac = ((now.minute() * 60 + now.second()) / 3600.0);
		int index = now.hour() > 12 ? now.hour() - 13 : now.hour() - 1;
		rpmPeriod = hourLows[index]
				- ((hourLows[index] - hourLows[index + 1]) * hourFrac);
		tach.setPeriod(rpmPeriod);

		uint8_t minute = now.minute();

		if (minute == 0)
			minutePeriod = 2000000;
		else if (minute == 1)
			minutePeriod = 1600000;
		else
			minutePeriod = 1000000.0 / ((float) minute * .59);

		Serial.println(minute);
		Serial.println(minutePeriod);
		speed.setPeriod(minutePeriod);
	}

	uint32_t pressTime = getButton();

	if (pressTime > 0) {
		Serial.print("Button press time = ");
		Serial.println(pressTime);
	}

	tach.process();
	speed.process();
}

uint32_t getButton() // this just returns how long the button was down, AFTER is goes high
{

	uint32_t currentMillis = millis();
	uint32_t buttonPressMillis = currentMillis;

	while (digitalRead(BUTTON_PIN) == LOW) {
		delay(10);
		buttonPressMillis = millis();
	}

	return buttonPressMillis - currentMillis;
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
