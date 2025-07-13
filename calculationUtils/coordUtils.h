#ifndef __SCORE__
#define __SCORE__
#include "coordUtils.h"
#include "../constants/numbers.h"

void updateTotalScore(short numberOfclosures) {
	if (scoresUpdated)
		return;
	
	for (short i = 0; i < numberOfClosures; i++) {
		totalScore += closures[i].closureCount * getColorScore(closures[i].closureColor);
	}
	
	scoresUpdated = true;
}

bool checkWinScore() {
	return totalScore >= winScore;
}

bool screenIsFilled() {
	short i,j;
	for (i=0; i<rowBoxNumbers; i++) {
		for (j=0; j<columnBoxNumbers; j++) {
			if (marked[i][j] == false)
				return false;
		}
	}
	
	return true;
}

bool checkLossCondition() {	
	if (screenIsFilled() && numberOfClosures > 0) {
		return true;
	}
	
	return false;
}


#endif
