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
	if (hmi.btn1.spressed(true) && hmi.btn2.spressed(true)) {
		release_to_quit = true;
	} else if (hmi.btn1.released() && hmi.btn2.released() && release_to_quit) {
		if (game.data.p1score + game.data.p2score == 9)
			game.init();
		else
			game.start_game();
	}
	score1.animate();
	score2.animate();
}
