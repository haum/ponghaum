#include "wait_players_screen.h"

#include "game_manager.h"
#include "../hmi/hmi_manager.h"

void WaitPlayersScreen::init() {
	ball_position.init();
	ball_position.loop(true);
	ball_position.updown(true);
	ball_position.set_duration(2000);
	ball_position.start();
	ball.init();
}

void WaitPlayersScreen::animate() {
	hmi.leds.clear();
	ball_position.animate();
	for (int i = -HMI_WIDTH; i < -HMI_WIDTH / 3; ++i) {
		if (hmi.btn1.clicked())
			hmi.leds.set(i, 0xff, 0, 0);
		else if (hmi.btn1.pressed())
			hmi.leds.set(i, 0x66, 0, 0);
		else
			hmi.leds.set(i, 0x22, 0, 0);
	}
	for (int i = HMI_WIDTH; i > HMI_WIDTH / 3; --i) {
		if (hmi.btn2.clicked())
			hmi.leds.set(i, 0, 0xff, 0);
		else if (hmi.btn2.pressed())
			hmi.leds.set(i, 0, 0x66, 0);
		else
			hmi.leds.set(i, 0, 0x22, 0);
	}
	bool dbl = hmi.btn1.pressed() && hmi.btn2.pressed();
	ball.set_shiny(dbl);
	ball.reverse(dbl);
	ball.set_position(30 * (ball_position * 2 - 1));
	ball.animate();
}
