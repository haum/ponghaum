#ifndef TEST_HARDWARE_SCREEN_H
#define TEST_HARDWARE_SCREEN_H

#include "game_manager.h"
#include "../anim/linear_animator.h"

class TestHardwareScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();

	private:
		LinearAnimator anim; // Animator
		bool quit; // Quit screen flag
};

#endif
