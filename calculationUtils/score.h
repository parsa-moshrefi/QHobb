#ifndef __SCORE__
#define __SCORE__
#include "coordUtils.h"
#include "numbers.h"

// todo: impl vanish & test this method
float scoreToVanish(pair<short, short> *closure, bool horizontal) {
	short i, boxNumbers;
	float score = 0.0f;
	boxNumbers = horizontal ? rowBoxNumbers : columnBoxNumbers;
	for (i=0; i<boxNumbers; i++) {
		if (darkFilled(closure[i])) {
			return score;
		}
		
		score += scorePerBoxVanish;
	}
	
	return score;
}

#endif
