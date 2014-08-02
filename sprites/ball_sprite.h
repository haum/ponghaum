#ifndef BALL_SPRITE_H
#define BALL_SPRITE_H

#include "sprite.h"
#include "../anim/linear_animator.h"

class BallSprite : public Sprite {
	public:
		/** Simple constructor **/
		BallSprite();

		/** Set ball shiny
		  * @param [in] active Effect active
		  */
		void set_shiny(bool active);

		/** Set queue behind ball effect
		  * @param [in] active Effect active
		  */
		void set_queue(bool active);

		/** Animation function **/
		virtual void animate();

	private:
		/** Init function **/
		virtual void init_sprite();

		bool shiny; /// Shiny flag
		bool queue; /// Queue flag

		float queue_length; /// Queue length
		float last_position; /// Registers last position to compute speed

		LinearAnimator flicker1; /// Flicker 1 animation
		LinearAnimator flicker2; /// Flicker 2 animation
};

#endif
