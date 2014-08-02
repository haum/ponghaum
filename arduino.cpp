#include "hmi/hmi_manager.h"
#include "game/game_manager.h"

void setup() {
	hmi.init();
	hmi.log("Bienvenue dans ponghaum !\n");
	game.init();
}

void loop() {
	hmi.loop_step();
	if (hmi.can_animate())
		game.animate();
}
