#ifndef PAD_SPRITE_H
#define PAD_SPRITE_H

#include "sprite.h"

class PadSprite : public Sprite {
	public:
		/** Animation function **/
		virtual void animate();

		/** Fire pad **/
		void fire(int size);

		/** Can fire again
		  * @return true fire time is ok
		  */
		bool can_fire();

	private:
		/** Init function **/
		virtual void init_sprite();

		int size; /// Size of pad
		LinearAnimator lightning; /// Lightning effect
};

#endif
