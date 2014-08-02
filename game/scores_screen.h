#ifndef SCORES_SCREEN_H
#define SCORES_SCREEN_H

#include "game_manager.h"

class ScoresScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();
};

#endif
