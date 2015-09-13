#include "test_hardware_screen.h"

#include "game_manager.h"

void TestHardwareScreen::init() {
	anim.init();
	anim.loop(true);
	anim.set_duration(3000);
	anim.start();
	quit = false;
	khroma.log("Hardware test\n");
}

void TestHardwareScreen::animate() {
	khroma.leds.clear();
	anim.animate();
	if (khroma.btn1.slpressed(true) && khroma.btn2.slpressed(true)) {
		quit = true;
	} else if (khroma.btn1.released() && khroma.btn2.released() && quit) {
		game.init();
	}
	const int segment = khroma.get_halfsize() * 2 / 15.0;
	int pos = anim * segment * 3;
	for (int i = -4; i < 3; i++) {
		khroma.leds.set_rgb(pos + i * segment * 3, 0xff, 0, 0);
		khroma.leds.set_rgb(pos + i * segment * 3 + 2 * segment, 0, 0xff, 0);
		khroma.leds.set_rgb(pos + i * segment * 3 + segment, 0, 0, 0xff);
	}
}
