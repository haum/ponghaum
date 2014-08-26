#include "hmi_manager.h"

#ifdef BUILD_PC
#include <stdio.h>
long long millis();
extern int pc_btn_pwr;
extern int pc_btn_1;
extern int pc_btn_2;
#else
#include "Arduino.h"
#endif

HmiManager hmi;

void HmiManager::init() {
	alim.init();
	btn1.init();
	btn2.init();
	leds.init();
	last_frame_time = millis();
	last_btn_time = millis();
	can_animate_flag = false;
#ifndef BUILD_PC
	pinMode(ARDUINO_PINS__BTN1, INPUT_PULLUP);
	pinMode(ARDUINO_PINS__BTN2, INPUT_PULLUP);
	Serial.begin(115200);
#endif
}

bool HmiManager::can_animate() {
	bool ret = can_animate_flag;
	return ret;
}

void HmiManager::loop_step() {
	long time = millis();
	if (can_animate_flag) {
		can_animate_flag = false;
		btn_power.endframe();
		btn1.endframe();
		btn2.endframe();
	}
	if (time >= last_btn_time + HMI_DTMS / 3) {
		last_btn_time = time;
#ifdef BUILD_PC
		btn_power.compute(pc_btn_pwr);
		btn1.compute(pc_btn_1);
		btn2.compute(pc_btn_2);
#else
		btn_power.compute(!digitalRead(ARDUINO_PINS__POWERSTOP));
		btn1.compute(!digitalRead(ARDUINO_PINS__BTN1));
		btn2.compute(!digitalRead(ARDUINO_PINS__BTN2));
#endif
		leds.update();
	}
	if (time >= last_frame_time + HMI_DTMS) {
		last_frame_time = time;
		can_animate_flag = true;
	}
}

void HmiManager::log(const char *msg) {
#ifdef BUILD_PC
	printf("%s", msg);
#else
	Serial.print(msg);
#endif
}

void HmiManager::log(int msg) {
#ifdef BUILD_PC
	printf("%d", msg);
#else
	Serial.print(msg);
#endif
}
