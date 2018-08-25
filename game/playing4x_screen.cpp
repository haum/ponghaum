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

void Playing4xScreen::onReceived(GameCommMsg type, char msg[4]) {
	if (type == GameCommMsg_INIT4) {
		if (msg[0] == 1) {
				ball.set_queue(true);
		} else {
				ball.set_queue(false);
		}
	}
}

/* Game mode: 0 -> 6
 * Ball direction: 0 -> 1
 * score_player_1: 0 -> 3
 * score_player_2: 0 -> 3
 * sender_id: 0 -> 254
 * receiver_id: 0 -> 254
 * msg[4]
 */
void Playing4xScreen::make_msg(
    int game_mode,
    int ball_direction,
    int score_player_1,
    int score_player_2,
    int sender_id,
    int receiver_id,
    char *msg) {

    int byte_1, byte_2, byte_3, byte_4;

    byte_1 = game_mode << 1;
    byte_1 += ball_direction;
    byte_1 = byte_1 << 2;
    byte_1 += score_player_1;
    byte_1 = byte_1 << 2;
    byte_1 += score_player_2;

    byte_2 = sender_id;

    byte_3 = receiver_id;

    byte_4 = 0;

    msg[0] = byte_1;
    msg[1] = byte_2;
    msg[2] = byte_3;
    msg[3] = byte_4;
}

char * Playing4xScreen::analyse_data(unsigned char *datas) {
    returned_data[0] = datas[0] >> 5;
    returned_data[1] = datas[0] >> 4 & 0x1;
    returned_data[2] = datas[0] >> 2 & 0x3;
    returned_data[3] = datas[0] & 0x3;
    returned_data[4] = datas[1];
    returned_data[5] = datas[2];
    returned_data[6] = datas[3];
    return returned_data;
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
			//quit = true;
			ball_direction = 1;
		}
		if (ball_position > khroma.get_halfsize()) {
			game.data.last_winner = PLAYER1;
			game.data.old_p1score = game.data.p1score;
			game.data.old_p2score = game.data.p2score;
			game.data.p1score += 1;
			if (game.mode == CONQUER && game.data.p2score + game.data.p1score >= MAX_POINTS)
				game.data.p2score = MAX_POINTS - game.data.p1score;
			//quit = true;
			ball_direction = -1;
		}

		// Play pads
		if (khroma.btn1.stouched() && pad1.can_fire() && !inhibed_controls) {
			if (game.data.playing4_master) {
					char msg[4];
					make_msg(0, 0, 0, 1, 0, 0, msg);
					khroma.send_data(GameCommMsg_INIT4, msg);
			}

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
			if (game.data.playing4_master) {
					char msg[4];
					make_msg(0, 0, 0, 0, 0, 0, msg);
					khroma.send_data(GameCommMsg_INIT4, msg);
			}
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
