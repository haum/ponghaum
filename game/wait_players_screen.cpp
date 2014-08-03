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
	ball.set_queue(true);
	pad1.init();
	pad1.reverse(true);
	pad2.init();
	quit = false;
	hmi.log("Attente des joueurs : maintenez les buzzers appuyés\n");
}

void WaitPlayersScreen::animate() {
	hmi.leds.clear();
	ball_position.animate();
	if (hmi.btn1.stouched() && pad1.can_fire()) {
		last_touch = PLAYER1;
		pad1.fire(20);
	}
	if (hmi.btn2.stouched() && pad2.can_fire()) {
		last_touch = PLAYER2;
		pad2.fire(20);
	}
	if (hmi.btn1.dpressed(true) && hmi.btn2.dpressed(true)) {
		game.test_hardware();
	} else if (hmi.btn1.slpressed(true) && hmi.btn2.slpressed(true)) {
		quit = true;
	} else if (hmi.btn1.released() && hmi.btn2.released() && quit) {
		game.data.last_winner = last_touch;
		game.restart_game();
	}

	ball.set_position(30 * (ball_position * 2 - 1));
	ball.set_shiny(quit);

	pad1.animate();
	pad2.animate();
	ball.animate();
}
