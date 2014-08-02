#include "hmi_manager.h"

#ifdef BUILD_PC
#include <SDL2/SDL.h>
long long millis();
extern SDL_Surface * screen;
extern int pc_btn_1;
extern int pc_btn_2;
#endif

HmiManager hmi;

void HmiButton::init() {
	is_pressed = false;
	is_clicked = false;
}

bool HmiButton::pressed() {
	return is_pressed;
}

bool HmiButton::clicked() {
	return is_clicked;
}

void HmiButton::compute(bool value) {
	is_pressed = value;
	is_clicked = false;
	if (value) {
		if (!is_clickedWait) {
			is_clicked = true;
			is_clickedWait = true;
		}
	} else {
		is_clickedWait = false;
	}
}

void HmiLeds::clear() {
#ifdef BUILD_PC
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
#endif
}

void HmiLeds::set(int led, unsigned char r, unsigned char g, unsigned char b) {
	if (led < -HMI_WIDTH || led > HMI_WIDTH) return;
#ifdef BUILD_PC
	if (screen) {
		SDL_Rect led_rect;
		led_rect.x = 320 + 4 * led;
		led_rect.y = (200 - 4) / 2;
		led_rect.w = 4;
		led_rect.h = 4;
		SDL_FillRect(screen, &led_rect, SDL_MapRGB(screen->format, r, g, b));
	}
#endif
}

void HmiManager::init() {
	btn1.init();
	btn2.init();
	last_frame_time = millis();
	can_animate_flag = false;
}

bool HmiManager::can_animate() {
	bool ret = can_animate_flag;
	can_animate_flag = false;
	return ret;
}

void HmiManager::loop_step() {
	long time = millis();
	if (time >= last_frame_time + HMI_DTMS) {
		last_frame_time = time;
		can_animate_flag = true;
		btn1.compute(pc_btn_1);
		btn2.compute(pc_btn_2);
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
