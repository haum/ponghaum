#include "hmi_alim.h"
#include "hmi_manager.h"

#ifdef BUILD_PC
#else
#include <Arduino.h>
#endif

void HmiAlim::init() {
#ifndef BUILD_PC
	pinMode(ARDUINO_PINS__POWERSTOP, INPUT_PULLUP);
	digitalWrite(ARDUINO_PINS__POWERCMD, HIGH);
	pinMode(ARDUINO_PINS__POWERCMD, OUTPUT);
	pinMode(ARDUINO_PINS__POWERGOOD, INPUT);
#endif
}

void HmiAlim::poweron() {
#ifndef BUILD_PC
	digitalWrite(ARDUINO_PINS__POWERCMD, LOW);
	while(digitalRead(ARDUINO_PINS__POWERGOOD) == LOW);
#endif
}

void HmiAlim::poweroff() {
#ifndef BUILD_PC
	digitalWrite(ARDUINO_PINS__POWERCMD, HIGH);
	while(digitalRead(ARDUINO_PINS__POWERGOOD) == HIGH);
#endif
}
