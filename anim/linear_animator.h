#ifndef LINEAR_ANIMATOR
#define LINEAR_ANIMATOR

#include "animator.h"

class LinearAnimator: public Animator {
	public:
		LinearAnimator();
		void set_knee(float k);
		virtual float transfert(float percent);

	private:
		float knee;
};

#endif
