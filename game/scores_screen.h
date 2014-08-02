#ifndef SCORES_SCREEN_H
#define SCORES_SCREEN_H

#include "game_manager.h"
#include "../sprites/score_sprite.h"

class ScoresScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();

	private:
		ScoreSprite score1; // Left score
		ScoreSprite score2; // Right score
		bool release_to_quit; // click flag
};

#endif
