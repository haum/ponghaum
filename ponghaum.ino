#include "khroma.h"
#include "game/game_manager.h"

PolychrHAUM <150, PIN__LEDSTRIP_DATA> khroma;

void animate() {
	game.animate();
}

void setup() {
	khroma.config_buttons(PIN__BTN1, PIN__BTN2);
	khroma.config_power(PIN__POWER_CMD, PIN__POWER_STATUS, PIN__POWER_BTN);
	khroma.config_light_ctrl(PIN__POTAR_LIGHT);
	khroma.config_speed_ctrl(PIN__POTAR_SPEED);
	khroma.config_animate(animate);
	khroma.setup();
	khroma.log("Bienvenue dans ponghaum !\n");
	game.init();
}

void loop() {
	khroma.loop_step();
}
