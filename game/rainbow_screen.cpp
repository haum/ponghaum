#include "rainbow_screen.h"

#include <stdint.h>
#include "../hmi/hmi_manager.h"

static uint8_t rainbow(uint16_t in) {
	while (in > 1536) in -= 1536;
	if (in > 1024)
		in = 0;
	else if (in > 768)
		in = 768 - in;
	else if (in >= 256)
		in = 255;
	return in;
}

void RainbowScreen::init() {
	anim.loop(true);
	anim.start();
}

void RainbowScreen::animate() {
	hmi.leds.clear();
	anim.animate();

	for (int i = -HMI_WIDTH; i < HMI_WIDTH; ++i) {
		hmi.leds.set(
			i,
			rainbow(i + anim*1536),
			rainbow(i + 512 + anim*1536),
			rainbow(i + 1024 + anim*1536)
		);
	}

	if (hmi.btn1.touched(true) && hmi.btn2.touched(true)) {
		game.initscreen();
	}
}
