#ifndef PLAYING_SCREEN_H
#define PLAYING_SCREEN_H

#include "game_manager.h"
#include "../sprites/ball_sprite.h"
#include "../sprites/pad_sprite.h"

class PlayingScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();

	private:
		BallSprite ball; // The ball
		PadSprite pad1; // Left pad
		PadSprite pad2; // Right pad

		float ball_position;
		float ball_local_speed;
		LinearAnimator ball_speed;
		int ball_direction;
		bool quit;
		bool inhibed_controls;
};

#endif
