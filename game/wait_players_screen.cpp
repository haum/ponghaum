#include "wait_players_screen.h"

#include "game_manager.h"

void WaitPlayersScreen::init() {
	ball_position.init();
	ball_position.loop(true);
	ball_position.updown(true);
	ball_position.set_duration(2000);
	ball_position.start();
	ball.init();
	ball.set_queue(true);
	pad1.init();
	pad1.reverse(true);
	pad2.init();
	quit = false;
	khroma.log("Attente des joueurs : maintenez les buzzers appuyés\n");
}

void WaitPlayersScreen::animate() {
	khroma.leds.clear();
	ball_position.animate();
	if (!quit) {
		bool start = false;
		ball.set_position((khroma.get_halfsize() - 25) * (ball_position * 2 - 1));
		if (khroma.btn1.stouched() && pad1.can_fire()) {
			last_touch = PLAYER1;
			pad1.fire(20);
		}
		if (khroma.btn2.stouched() && pad2.can_fire()) {
			last_touch = PLAYER2;
			pad2.fire(20);
		}
		if (khroma.btn1.dpressed(true) && khroma.btn2.dpressed(true)) {
			game.mode = CONQUER;
			start = true;
			//game.test_hardware();
		} else if (khroma.btn1.slpressed(true) && khroma.btn2.slpressed(true) ) {
			game.mode = NORMAL;
			start = true;
		}
		if (start) {
			if (game.mode == CONQUER) khroma.log("Conqueror !");
			quit = true;
			ball_position.set_duration(500);
			ball_position.loop(false);
			ball_position.updown(false);
			ball_position.start();
			int target = (last_touch == PLAYER1 ? -khroma.get_halfsize() : khroma.get_halfsize());
			quit_start = ball.get_position();
			quit_dist = target - quit_start;
		}

	} else {
		ball.set_shiny(true);
		ball.set_position(quit_start + ball_position * quit_dist);
		if (khroma.btn1.released() && khroma.btn2.released() && ball_position.get_value() == 1) {
			game.data.last_winner = last_touch;
			game.restart_game();
		}
	}

	pad1.animate();
	pad2.animate();
	ball.animate();
}
