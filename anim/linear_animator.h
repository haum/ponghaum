#ifndef LINEAR_ANIMATOR
#define LINEAR_ANIMATOR

#include "animator.h"

class LinearAnimator: public Animator {
	virtual float transfert(float percent) {
		return percent;
	}
};

#endif
