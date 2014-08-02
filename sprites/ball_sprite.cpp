#include "ball_sprite.h"

BallSprite::BallSprite() : shiny(false), queue(false) {
}

void BallSprite::set_shiny(bool active) {
	shiny = active;
}

void BallSprite::set_queue(bool active) {
	queue = active;
	queue_length = 0;
}

void BallSprite::init_sprite() {
	shiny = false;
	queue = false;
	flicker1.init();
	flicker1.loop(true);
	flicker1.updown(true);
	flicker1.set_duration(800);
	flicker1.start();
	flicker2.init();
	flicker2.loop(true);
	flicker2.updown(true);
	flicker2.set_duration(400);
	flicker2.start();
}

void BallSprite::animate() {
	flicker1.animate();
	flicker2.animate();
	if (queue) {
		queue_length += (get_position() - last_position);
		if (queue_length > 10) queue_length = 10;
		if (queue_length < -10) queue_length = -10;
		int imax = get_reversed() ? -queue_length : queue_length;
		for (int i = 1; i < imax; ++i)
			if (shiny)
				draw(-i, 0, 120 - 12 * i, 255 - 12 * i);
			else
				draw(-i, 255 - 12 * i, 120 - 12 * i, 0);
		for (int i = -1; i > imax; --i)
			if (shiny)
				draw(-i, 0, 120 + 12 * i, 255 + 12 * i);
			else
				draw(-i, 255 + 12 * i, 120 + 12 * i, 0);
	}
	float factor = flicker1.get_value() / 2 + 0.5;
	draw(0, 0xff * factor, 0xff * factor, 0xff * factor);
	last_position = get_position();
}
