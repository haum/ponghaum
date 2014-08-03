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

		/** Fade score out **/
		void fadeout();

		/** Is fadeout animation finished
		  * @return true when finished
		  */
		bool fadeout_finished();

	private:
		/** Init function **/
		virtual void init_sprite();

		int score; /// Score to show
		LinearAnimator anim; /// Animation at start
		LinearAnimator animloop; /// Animation loop
		LinearAnimator animfadeout; /// Animation fade out
};

#endif
