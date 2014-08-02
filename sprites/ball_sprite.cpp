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
}

void BallSprite::animate() {
	if (queue) {
		queue_length += (get_position() - last_position);
		if (queue_length > 10) queue_length = 10;
		if (queue_length < -10) queue_length = -10;
		int imax = get_reversed() ? -queue_length : queue_length;
		for (int i = 1; i < imax; ++i)
			draw(-i, 255 - 12 * i, 120 - 12 * i, 0);
		for (int i = -1; i > imax; --i)
			draw(-i, 255 + 12 * i, 120 + 12 * i, 0);
	}
	if (shiny)
		draw(0, 0, 0x99, 0xff);
	else
		draw(0, 0xff, 0xff, 0xff);
	last_position = get_position();
}
