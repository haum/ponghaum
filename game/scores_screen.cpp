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

	fct = 0;
}

void ScoresScreen::animate() {
	hmi.leds.clear();
	score1.animate();
	score2.animate();

	if (score1.fadeout_finished() && score2.fadeout_finished()) {
		if (hmi.btn1.spressed(true) || fct) {
			hmi.leds.set(-HMI_WIDTH, 0xAA, 0xAA, 0xAA);
		}
		if (hmi.btn2.spressed(true) || fct) {
			hmi.leds.set(+HMI_WIDTH, 0xAA, 0xAA, 0xAA);
		}
		if (hmi.btn1.dpressed(true)) {
			hmi.leds.set(-HMI_WIDTH, 0xAA, 0, 0);
		}
		if (hmi.btn2.dpressed(true)) {
			hmi.leds.set(+HMI_WIDTH, 0xAA, 0, 0);
		}
	}

	if (hmi.btn1.dpressed(true) && hmi.btn2.dpressed(true)) {
		fct = &GameManager::init;
		score1.fadeout();
		score2.fadeout();
	} else if (hmi.btn1.spressed(true) && hmi.btn2.spressed(true)) {
		if (game.data.p1score + game.data.p2score == 9) {
			fct = &GameManager::init;
			score1.fadeout();
			score2.fadeout();
		} else {
			fct = &GameManager::play;
			score1.fadeout();
			score2.fadeout();
		}
	} else if (hmi.btn1.released() && hmi.btn2.released() && fct && score1.fadeout_finished() && score2.fadeout_finished()) {
		(game.*fct)();
	}
}
