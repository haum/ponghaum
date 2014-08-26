#include "poweroff_screen.h"

#include "game_manager.h"
#include "../hmi/hmi_manager.h"

void PoweroffScreen::init() {
	hmi.alim.poweroff();
}

void PoweroffScreen::animate() {
	hmi.leds.clear();
	if (hmi.btn1.stouched() || hmi.btn2.stouched() || hmi.btn_power.stouched()) {
		hmi.alim.poweron();
		game.initscreen();
	}
}
