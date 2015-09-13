#include "poweroff_screen.h"

#include "game_manager.h"

void PoweroffScreen::init() {
	khroma.power.poweroff();
	was_powered = false;
}

void PoweroffScreen::animate() {
	bool poweron = false;
	if (!was_powered && khroma.power.is_powered())
		poweron = true;
	was_powered = khroma.power.is_powered();
	khroma.leds.clear();
	if (khroma.btn1.stouched() || khroma.btn2.stouched() || poweron) {
		game.initscreen();
	}
}
