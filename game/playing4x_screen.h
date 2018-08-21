#ifndef PLAYING4X_SCREEN_H
#define PLAYING4X_SCREEN_H

#include "game_manager.h"
#include "../sprites/ball_sprite.h"
#include "../sprites/pad_sprite.h"

class Playing4xScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();

		/** Communication function **/
		virtual void onReceived(GameCommMsg, char[4]);

		virtual void generate_random_direction();

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
		bool half_passed;
		int old_direction;
		int random_direction;
};

#endif
