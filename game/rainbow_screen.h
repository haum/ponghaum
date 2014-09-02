#ifndef RAINBOW_SCREEN_H
#define RAINBOW_SCREEN_H

#include "game_manager.h"

class RainbowScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();

	private:
		LinearAnimator anim;
};

#endif
