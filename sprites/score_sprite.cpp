#include "score_sprite.h"
#include "../hmi/hmi_manager.h"

void ScoreSprite::init_sprite() {
	anim.init();
	anim.set_duration(500);
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
	int imax = score * anim * 2 * HMI_WIDTH / 5.0;
	unsigned char r, g, b;
	r = get_reversed() ? 0xff : 0x00;
	g = get_reversed() ? 0x00 : 0xff;
	b = get_reversed() ? 0xff : 0xff;
	float alpha = (1 - animfadeout);
	for (int i = HMI_WIDTH; i > HMI_WIDTH - imax; --i)
		draw(i, r * anim * alpha, g * anim * alpha, b * anim * alpha);
	draw(HMI_WIDTH - animloop * imax, r/2 * alpha, g/2 * alpha, b/2 * alpha);
}

void ScoreSprite::fadeout() {
	animfadeout.start();
}

bool ScoreSprite::fadeout_finished() {
	return !animfadeout.running();
}
