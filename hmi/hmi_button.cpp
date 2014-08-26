#include "hmi_button.h"

void HmiButton::init() {
	state = HmiButtonState_NOTHING;
	press = HmiButtonPress_NOTHING;
	timer = 0;
}

bool HmiButton::released() {
	return (press == HmiButtonPress_NOTHING && state == HmiButtonState_NOTHING);
}

bool HmiButton::sclicked() {
	return (press == HmiButtonPress_CLICKED1);
}

bool HmiButton::spressed(bool still) {
	return (
		(press == HmiButtonPress_PRESSED1) ||
		(still && (state == HmiButtonState_FT1 || state == HmiButtonState_WT1))
	);
}

bool HmiButton::stouched(bool still) {
	return (sclicked() || spressed(still));
}

bool HmiButton::slpressed(bool still) {
	return (
		(press == HmiButtonPress_LONGPRESSED1) ||
		(still && state == HmiButtonState_WT1)
	);
}

bool HmiButton::dclicked() {
	return (press == HmiButtonPress_CLICKED2);
}

bool HmiButton::dpressed(bool still) {
	return (
		(press == HmiButtonPress_PRESSED2) ||
		(still && (state == HmiButtonState_FT2 || state == HmiButtonState_WT2))
	);
}

bool HmiButton::dtouched(bool still) {
	return (dclicked() || dpressed(still));
}

bool HmiButton::dlpressed(bool still) {
	return (
		(press == HmiButtonPress_LONGPRESSED2) ||
		(still && state == HmiButtonState_WT2)
	);
}

bool HmiButton::touched(bool still) {
	return (stouched(still) || dtouched(still));
}

void HmiButton::endframe() {
	press = HmiButtonPress_NOTHING;
}

void HmiButton::compute(bool value) {
	timer += 2 * value - 1;
	switch (state) {
		case HmiButtonState_NOTHING:
			if (timer < 0) {
				timer = 0;
			} else if (timer == 8) {
				timer = 0;
				state = HmiButtonState_HT1;
			}
			break;

		case HmiButtonState_HT1:
			if (timer == 16) {
				state = HmiButtonState_FT1;
				press = HmiButtonPress_PRESSED1;
				timer = 0;
			} else if (timer == -3) {
				state = HmiButtonState_HB1;
				timer = 0;
			}
			break;

		case HmiButtonState_HB1:
			if (timer == 8) {
				state = HmiButtonState_HT2;
				timer = 0;
			} else if (timer == -25) {
				state = HmiButtonState_NOTHING;
				press = HmiButtonPress_CLICKED1;
				timer = 0;
			}
			break;

		case HmiButtonState_HT2:
			if (timer == 8) {
				state = HmiButtonState_FT2;
				press = HmiButtonPress_PRESSED2;
				timer = 0;
			} else if (timer == -3) {
				state = HmiButtonState_HB2;
				timer = 0;
			}
			break;

		case HmiButtonState_HB2:
			if (timer == 8) {
				state = HmiButtonState_FT2;
				timer = 0;
			} else if (timer == -8) {
				state = HmiButtonState_NOTHING;
				press = HmiButtonPress_CLICKED2;
				timer = 0;
			}
			break;

		case HmiButtonState_FT1:
			if (timer > 80) {
				state = HmiButtonState_WT1;
				press = HmiButtonPress_LONGPRESSED1;
				timer = 0;
			} else if (timer == -10) {
				state = HmiButtonState_NOTHING;
				timer = 0;
			}
			break;

		case HmiButtonState_FT2:
			if (timer > 80) {
				state = HmiButtonState_WT2;
				press = HmiButtonPress_LONGPRESSED2;
				timer = 0;
			} else if (timer == -10) {
				state = HmiButtonState_NOTHING;
				timer = 0;
			}
			break;

		case HmiButtonState_WT1:
		case HmiButtonState_WT2:
			if (timer > 0) {
				timer = 0;
			} else if (timer == -10) {
				state = HmiButtonState_NOTHING;
				timer = 0;
			}
			break;
	}
}
