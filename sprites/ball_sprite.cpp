#include "ball_sprite.h"

BallSprite::BallSprite() : shiny(false) {
}

void BallSprite::set_shiny(bool active) {
	shiny = active;
}

void BallSprite::init_sprite() {
	shiny = false;
}

void BallSprite::animate() {
	if (shiny)
		draw(0, 0, 0x99, 0xff);
	else
		draw(0, 0xff, 0xff, 0xff);
}
