#ifndef BALL_SPRITE_H
#define BALL_SPRITE_H

#include "sprite.h"

class BallSprite : public Sprite {
	public:
		/** Simple constructor **/
		BallSprite();

		/** Set ball shiny
		  * @param [in] active Effect active
		  */
		void set_shiny(bool active);

		/** Animation function **/
		virtual void animate();

	private:
		/** Init function **/
		virtual void init_sprite();

		bool shiny; // Shiny flag
};

#endif
