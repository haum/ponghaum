#include "wait_players_screen.h"

#include "game_manager.h"
#include "../hmi/hmi_manager.h"

void WaitPlayersScreen::init() {
	ball.init();
	ball_position = 0;
}

void WaitPlayersScreen::animate() {
	hmi.leds.clear();
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
	ball_position += 0.3;
	if (ball_position > 15) ball_position = 0;
	ball.set_position(ball_position);
	ball.animate();
}
