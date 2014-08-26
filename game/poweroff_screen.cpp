#include "poweroff_screen.h"

#include "game_manager.h"
#include "../hmi/hmi_manager.h"

void PoweroffScreen::init() {
	hmi.alim.poweroff();
}

void PoweroffScreen::animate() {
	hmi.leds.clear();
	if (hmi.btn1.spressed() || hmi.btn2.spressed() || hmi.btn_power.spressed()) {
		hmi.alim.poweron();
		game.initscreen();
	}
}
