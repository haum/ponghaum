#ifndef SCORE_SPRITE_H
#define SCORE_SPRITE_H

#include "sprite.h"
#include "../anim/linear_animator.h"

class ScoreSprite : public Sprite {
	public:
		/** Animation function **/
		virtual void animate();

		/** Set score
		  * @param [in] score Score to set
		  */
		void set_score(int score);

	private:
		/** Init function **/
		virtual void init_sprite();

		int score; /// Score to show
		LinearAnimator anim; /// Animation at start
		LinearAnimator animloop; /// Animation loop
};

#endif
