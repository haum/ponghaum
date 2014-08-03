#include "hmi_manager.h"

#ifdef BUILD_PC
#include <stdio.h>
long long millis();
extern int pc_btn_1;
extern int pc_btn_2;
#endif

HmiManager hmi;

void HmiManager::init() {
	btn1.init();
	btn2.init();
	last_frame_time = millis();
	last_btn_time = millis();
	can_animate_flag = false;
}

bool HmiManager::can_animate() {
	bool ret = can_animate_flag;
	return ret;
}

void HmiManager::loop_step() {
	long time = millis();
	if (can_animate_flag) {
		can_animate_flag = false;
		btn1.endframe();
		btn2.endframe();
	}
	if (time >= last_btn_time + HMI_DTMS / 3) {
		last_btn_time = time;
		btn1.compute(pc_btn_1);
		btn2.compute(pc_btn_2);
	}
	if (time >= last_frame_time + HMI_DTMS) {
		last_frame_time = time;
		can_animate_flag = true;
	}
}

void HmiManager::log(const char *msg) {
#ifdef BUILD_PC
	printf("%s", msg);
#endif
}

void HmiManager::log(int msg) {
#ifdef BUILD_PC
	printf("%d", msg);
#endif
}
