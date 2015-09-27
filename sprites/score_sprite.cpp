#include "score_sprite.h"
#include "../game/game_manager.h"

void ScoreSprite::init_sprite() {
	anim.init();
	anim.set_duration(700);
	animloop.init();
	animloop.set_duration(1000);
	animloop.loop(true);
	animloop.start();
	animfadeout.init();
}

void ScoreSprite::set_score(int score) {
	this->score = score;
	anim.start();
}

void ScoreSprite::animate() {
	anim.animate();
	animloop.animate();
	animfadeout.animate();

	int score_unit_length = 2 * khroma.get_halfsize() / MAX_POINTS;
	int old_score, score_delta;
	if (get_reversed()) {
		old_score = game.data.old_p1score;
		score_delta = game.data.p1score - old_score;
	} else {
		old_score = game.data.old_p2score;
		score_delta = game.data.p2score - old_score;
	}

	int imax = (old_score + anim * score_delta ) * score_unit_length;

	unsigned char r, g, b, sep_r, sep_g, sep_b;
	r = get_reversed() ? 0xff : 0x00;
	g = get_reversed() ? 0x00 : 0xff;
	b = get_reversed() ? 0xff : 0xff;
	sep_r = 0xFF ^ r;
	sep_b = 0xFF ^ b;
	sep_g = 0xFF ^ g;
	float alpha = (1 - animfadeout) * anim;

	int next_sep = score_unit_length - 1;
	for (int i = khroma.get_halfsize(); i > khroma.get_halfsize() - imax; --i) {
		if ( i == khroma.get_halfsize() - next_sep) {
			draw(i, sep_r * alpha, sep_g * alpha, sep_b * alpha);
			next_sep += score_unit_length;
		} else {
			draw(i, r * alpha, g * alpha, b * alpha);
		}
	}
	draw(khroma.get_halfsize() - animloop * imax, r/2 * alpha, g/2 * alpha, b/2 * alpha);
}

void ScoreSprite::fadeout() {
	animfadeout.start();
}

bool ScoreSprite::fadeout_finished() {
	return !animfadeout.running();
}
