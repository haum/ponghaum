#ifndef POWEROFF_SCREEN_H
#define POWEROFF_SCREEN_H

#include "game_manager.h"

class PoweroffScreen : public GameScreen {
	private:
		/** Power-on detector helper **/
		bool was_powered;

	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();
};

#endif
