#include "playing_screen.h"

#include "game_manager.h"
#include "../hmi/hmi_manager.h"

void PlayingScreen::init() {
	ball.init();
	ball.set_queue(true);
	pad1.init();
	pad1.reverse(true);
	pad2.init();

	ball_local_speed = 0;
	if (game.data.last_winner == PLAYER1) {
		ball_position = HMI_WIDTH - 21;
		ball_direction = -1;
	} else {
		ball_position = 21 - HMI_WIDTH;
		ball_direction = 1;
	}

	ball_speed.init();
	ball_speed.set_duration(60000);
	ball_speed.start();

	hmi.log("C'est (re)parti !\n");
}

void PlayingScreen::animate() {
	hmi.leds.clear();
	ball_speed.animate();

	// Compute ball speed and new position
	float real_speed = HMI_DTMS / (600.0 + (1 - ball_speed) * 1000.0 - ball_local_speed) * HMI_WIDTH * 2;
	if (real_speed > HMI_DTMS / 500.0 * HMI_WIDTH * 2)
		real_speed = HMI_DTMS / 500.0 * HMI_WIDTH * 2;
	ball_position += real_speed * ball_direction;
	ball.set_shiny(
		(HMI_WIDTH - 20 < ball_position && ball_direction > 0) ||
		(20 - HMI_WIDTH > ball_position && ball_direction < 0)
	);
	ball.set_position(ball_position);

	// Check for win
	if (ball_position < -HMI_WIDTH) {
		game.data.last_winner = PLAYER2;
		game.data.p2score += 1;
		game.show_scores();
	}
	if (ball_position > HMI_WIDTH) {
		game.data.last_winner = PLAYER1;
		game.data.p1score += 1;
		game.show_scores();
	}

	// Play pads
	if (hmi.btn1.stouched() && pad1.can_fire()) {
		if (20 - HMI_WIDTH > ball_position) {
			pad1.fire(HMI_WIDTH + ball_position);
			ball_direction = 1;
			ball_local_speed = 50 * (20 - HMI_WIDTH - ball_position);
		} else {
			pad1.fire(20);
		}
	}
	if (hmi.btn2.stouched() && pad2.can_fire()) {
		if (HMI_WIDTH - 20 < ball_position) {
			pad2.fire(HMI_WIDTH - ball_position);
			ball_direction = -1;
			ball_local_speed = 50 * (20 - HMI_WIDTH + ball_position);
		} else {
			pad2.fire(20);
		}
	}

	// Update all
	pad1.animate();
	pad2.animate();
	ball.animate();
}
