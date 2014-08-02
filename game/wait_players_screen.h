#ifndef WAIT_PLAYERS_SCREEN_H
#define WAIT_PLAYERS_SCREEN_H

#include "game_manager.h"
#include "../sprites/ball_sprite.h"

class WaitPlayersScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();

	private:
		BallSprite ball; // The ball
		float ball_position;
};

#endif
