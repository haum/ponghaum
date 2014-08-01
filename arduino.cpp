#include "hmi/hmi_manager.h"
#include "game/game_manager.h"

void setup() {
	hmi.init();
	game.init();

	hmi.log("Bienvenue dans ponghaum !\n");
}

void loop() {
	hmi.loop_step();
	if (hmi.can_animate())
		game.animate();
}
