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

		/** Set queue behind ball effect
		  * @param [in] active Effect active
		  */
		void set_queue(bool active);

		void set_color(uint8_t r, uint8_t g, uint8_t b);

		/** Animation function **/
		virtual void animate();

	private:
		/** Init function **/
		virtual void init_sprite();

		bool shiny; /// Shiny flag
		bool queue; /// Queue flag

		uint8_t red;
		uint8_t green;
		uint8_t blue;

		float queue_length; /// Queue length
		float last_position; /// Registers last position to compute speed
};

#endif
