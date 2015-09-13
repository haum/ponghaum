#include "sprite.h"

Sprite::Sprite() : linked_to(0), reversed(false), position(0) {
}

void Sprite::init() {
	linked_to = 0;
	reversed = false;
	position = 0;
	init_sprite();
}

void Sprite::link_to(Sprite * l) {
	linked_to = l;
}

void Sprite::reverse(bool active) {
	if (reversed ^ active)
		position = -position;
	reversed = active;
}

void Sprite::set_position(float pos) {
	if (reversed) pos = -pos;
	position = pos;
}

float Sprite::get_position() {
	return position;
}

float Sprite::get_abs_position() {
	if (linked_to)
		return linked_to->get_abs_position() + position;
	else
		return position;
}

bool Sprite::get_reversed() {
	return reversed;
}

void Sprite::draw(int led, unsigned char r, unsigned char g, unsigned char b) {
	if (reversed) led = -led;
	khroma.leds.set_rgb(get_abs_position() + led, r, g, b);
}
