#include "linear_animator.h"

LinearAnimator::LinearAnimator(): knee(1) {
}

void LinearAnimator::set_knee(float k) {
	knee = k;
}

float LinearAnimator::transfert(float percent) {
	if (knee == 1) return percent;
	else if (percent >= knee)
		return 1 + (knee/(1-knee)) - percent / (1-knee);
	else
		return percent / knee;
}
