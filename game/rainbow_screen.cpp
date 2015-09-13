#include "rainbow_screen.h"

#include <stdint.h>

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
	khroma.leds.clear();
	anim.animate();

	for (int i = -khroma.get_halfsize(); i < khroma.get_halfsize(); ++i) {
		khroma.leds.set_rgb(
			i,
			rainbow(i + anim*1536),
			rainbow(i + 512 + anim*1536),
			rainbow(i + 1024 + anim*1536)
		);
	}

	if (khroma.btn1.touched(true) && khroma.btn2.touched(true)) {
		game.initscreen();
	}
}
