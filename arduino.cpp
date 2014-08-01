#include "hmi/hmi_manager.h"

void setup() {
	hmi.init();
	hmi.log("Bienvenue dans ponghaum !\n");
}

void loop() {
	hmi.loop_step();

	if (hmi.can_animate()) {
		hmi.leds.clear();
		for (int i = 0; i < HMI_NB_LEDS / 2; ++i) {
			if (hmi.btn1.clicked())
				hmi.leds.set(i, 0xff, 0, 0);
			else if (hmi.btn1.pressed())
				hmi.leds.set(i, 0x66, 0, 0);
			else
				hmi.leds.set(i, 0x22, 0, 0);
		}
		for (int i = HMI_NB_LEDS / 2; i < HMI_NB_LEDS; ++i) {
			if (hmi.btn2.clicked())
				hmi.leds.set(i, 0, 0xff, 0);
			else if (hmi.btn2.pressed())
				hmi.leds.set(i, 0, 0x66, 0);
			else
				hmi.leds.set(i, 0, 0x22, 0);
		}
	}
}
