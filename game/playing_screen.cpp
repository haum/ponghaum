#include "playing_screen.h"

#include "../hmi/hmi_manager.h"

void PlayingScreen::init() {
	hmi.log("C'est (re)parti !\n");
}

void PlayingScreen::animate() {
	hmi.leds.clear();
}
