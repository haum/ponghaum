#ifndef PLAYING_SCREEN_H
#define PLAYING_SCREEN_H

#include "game_manager.h"

class PlayingScreen : public GameScreen {
	public:
		/** Init function **/
		virtual void init();

		/** Animate function **/
		virtual void animate();
};

#endif
