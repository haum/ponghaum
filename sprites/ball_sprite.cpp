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
	queue_length = 0;
	last_position = get_position();
}

void BallSprite::set_color(uint8_t r, uint8_t g, uint8_t b){
	red = r;
	green = g;
	blue = b;
}

void BallSprite::animate() {
	if (queue) {
		queue_length += (get_position() - last_position);
		queue_length -= queue_length / 10;
		if (queue_length > 10) queue_length = 10;
		if (queue_length < -10) queue_length = -10;
		int imax = get_reversed() ? -queue_length : queue_length;
		for (int i = 1; i < imax; ++i)
			if (shiny)
				draw(-i, 0, 255 - 12 * i, 120 - 12 * i);
			else
				draw(-i, 255 - 12 * i, 120 - 12 * i, 0);
		for (int i = -1; i > imax; --i)
			if (shiny)
				draw(-i, 0, 255 + 12 * i, 120 + 12 * i);
			else
				draw(-i, 255 + 12 * i, 120 + 12 * i, 0);
	}
	draw(0, red, green, blue);
	last_position = get_position();
}
