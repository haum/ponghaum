#include "scores_screen.h"

#include "../hmi/hmi_manager.h"

void ScoresScreen::init() {
	hmi.log("Scores : ");
	hmi.log(game.data.p1score);
	hmi.log(" - ");
	hmi.log(game.data.p2score);
	hmi.log("\n");

	score1.init();
	score1.reverse(true);
	score1.set_score(game.data.p1score);

	score2.init();
	score2.set_score(game.data.p2score);

	release_to_quit = false;
}

void ScoresScreen::animate() {
	hmi.leds.clear();
	if (hmi.btn1.pressed() && hmi.btn2.pressed()) {
		release_to_quit = true;
	} else if (!hmi.btn1.pressed() && !hmi.btn2.pressed() && release_to_quit) {
		if (game.data.p1score + game.data.p2score == 9)
			game.init();
		else
			game.start_game();
	}
	score1.animate();
	score2.animate();
}
