#include "hmi_button.h"

void HmiButton::init() {
	is_pressed = false;
	is_clicked = false;
}

bool HmiButton::pressed() {
	return is_pressed;
}

bool HmiButton::clicked() {
	return is_clicked;
}

void HmiButton::compute(bool value) {
	is_pressed = value;
	is_clicked = false;
	if (value) {
		if (!is_clickedWait) {
			is_clicked = true;
			is_clickedWait = true;
		}
	} else {
		is_clickedWait = false;
	}
}
