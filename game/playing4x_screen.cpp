#include "playing4x_screen.h"

#include "game_manager.h"
#include <stdlib.h>     /* srand, rand */

void Playing4xScreen::generate_random_direction() {
	old_direction = ball_direction;

	while (old_direction != ball_direction) {
		random_direction = rand() % 2;
		khroma.log(random_direction);
		if (random_direction == 0) {
			ball_direction = -1;
		} else {
			ball_direction = 1;
		}
		ball_position = 0;
		half_passed = true;
	}
}

void Playing4xScreen::init() {
	ball.init();
	ball.set_queue(true);
	ball.set_color(0xff, 0xff, 0xff);
	pad1.init();
	pad1.reverse(true);
	pad2.init();

	ball_local_speed = 0;
	if (game.data.last_winner == PLAYER2) {
		ball_position = khroma.get_halfsize();
		ball_direction = -1;
	} else {
		ball_position = -khroma.get_halfsize();
		ball_direction = 1;
	}
	inhibed_controls = true;

	ball_speed.init();
	if (game.mode == CONQUER) {
		ball_speed.set_duration(10000);
	} else if (game.mode == NORMAL) {
		ball_speed.set_duration(21000);
	}
	ball_speed.start();

	quit = 0;

	khroma.log("C'est (re)parti !\n");
}

void Playing4xScreen::animate() {
	khroma.leds.clear();
	ball_speed.animate();

	if (!half_passed) {
		if (ball_direction == 1) {
			if (ball_position > 0) {
				generate_random_direction();
			}
		} else {
			if (ball_position < 0) {
				generate_random_direction();
			}
		}
	}

	// Compute ball speed and new position
	float real_speed = polychrhaum::dtms / (800.0 + (1 - ball_speed) * 4000.0 - ball_local_speed) * khroma.get_halfsize() * 2;
	if (real_speed > polychrhaum::dtms / 500.0 * khroma.get_halfsize() * 2)
		real_speed = polychrhaum::dtms / 500.0 * khroma.get_halfsize() * 2;
	ball_position += real_speed * ball_direction;
	ball.set_shiny(
		(khroma.get_halfsize() - 20 < ball_position && ball_direction > 0) ||
		(20 - khroma.get_halfsize() > ball_position && ball_direction < 0)
	);
	ball.set_position(ball_position);
	if (ball_position < khroma.get_halfsize() - 21 && ball_position > 21 - khroma.get_halfsize())
		inhibed_controls = false;

	if (!quit) {
		// Check for win
		if (ball_position < -khroma.get_halfsize()) {
			game.data.last_winner = PLAYER2;
			game.data.old_p1score = game.data.p1score;
			game.data.old_p2score = game.data.p2score;
			game.data.p2score += 1;
			if (game.mode == CONQUER && game.data.p2score + game.data.p1score >= MAX_POINTS)
				game.data.p1score = MAX_POINTS - game.data.p2score;
			quit = true;
		}
		if (ball_position > khroma.get_halfsize()) {
			game.data.last_winner = PLAYER1;
			game.data.old_p1score = game.data.p1score;
			game.data.old_p2score = game.data.p2score;
			game.data.p1score += 1;
			if (game.mode == CONQUER && game.data.p2score + game.data.p1score >= MAX_POINTS)
				game.data.p2score = MAX_POINTS - game.data.p1score;
			quit = true;
		}

		// Play pads
		if (khroma.btn1.stouched() && pad1.can_fire() && !inhibed_controls) {
			if (20 - khroma.get_halfsize() > ball_position) {
				pad1.fire(khroma.get_halfsize() + ball_position);
				ball_direction = 1;
				ball_local_speed = 50 * (20 - khroma.get_halfsize() - ball_position);
				half_passed = false;
			} else {
				pad1.fire(20);
			}
		}
		if (khroma.btn2.stouched() && pad2.can_fire() && !inhibed_controls) {
			if (khroma.get_halfsize() - 20 < ball_position) {
				pad2.fire(khroma.get_halfsize() - ball_position);
				ball_direction = -1;
				ball_local_speed = 50 * (20 - khroma.get_halfsize() + ball_position);
				half_passed = false;
			} else {
				pad2.fire(20);
			}
		}
		ball.animate();
	} else if (pad1.can_fire() && pad2.can_fire()) {
		game.show_scores();
	}

	// Update all
	pad1.animate();
	pad2.animate();
}
