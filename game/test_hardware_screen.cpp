#include "test_hardware_screen.h"

#include "game_manager.h"
#include "../hmi/hmi_manager.h"

void TestHardwareScreen::init() {
	anim.init();
	anim.loop(true);
	anim.set_duration(3000);
	anim.start();
	quit = false;
	hmi.log("Hardware test\n");
}

void TestHardwareScreen::animate() {
	hmi.leds.clear();
	anim.animate();
	if (hmi.btn1.slpressed(true) && hmi.btn2.slpressed(true)) {
		quit = true;
	} else if (hmi.btn1.released() && hmi.btn2.released() && quit) {
		game.init();
	}
	const int segment = HMI_WIDTH * 2 / 15.0;
	int pos = anim * segment * 3;
	for (int i = -4; i < 3; i++) {
		hmi.leds.set(pos + i * segment * 3, 0xff, 0, 0);
		hmi.leds.set(pos + i * segment * 3 + 2 * segment, 0, 0xff, 0);
		hmi.leds.set(pos + i * segment * 3 + segment, 0, 0, 0xff);
	}
}
