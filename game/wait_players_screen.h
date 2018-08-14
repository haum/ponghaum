#ifndef WAIT_PLAYERS_SCREEN_H
#define WAIT_PLAYERS_SCREEN_H

#include "game_manager.h"
#include "../sprites/ball_sprite.h"
#include "../sprites/pad_sprite.h"

class WaitPlayersScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Communication function **/
		virtual void onReceived(GameCommMsg, char[4]);

		/** Animate function **/
		virtual void animate();

	private:
		LinearAnimator ball_position;
		BallSprite ball; // The ball
		PadSprite pad1; // Left pad
		PadSprite pad2; // Right pad
		GamePlayer last_touch; // Which button is the last touch
		bool quit; // Quit screen flag
		float quit_start; // Start of quit animation;
		float quit_dist; // Distance of the quit animation
};

#endif
