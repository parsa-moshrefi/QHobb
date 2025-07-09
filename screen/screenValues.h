#ifndef __SCREENVALS__
#define __SCREENVALS__

#include <list>
#include <utility>
#include "../calculationUtils/coordUtils.h"
#include "../constants/numbers.h"
#include "../constants/types.h"

using namespace std;

void initScreenVals() {
	short i, j;
	heights = (short*) malloc(sizeof(short) * rowBoxNumbers);
	marked = (bool**) malloc(sizeof(bool*) * rowBoxNumbers);
	closures = (ClosureHolder*) malloc(sizeof(ClosureHolder) * maxClosuresNumber);
	for (i=0; i<rowBoxNumbers; i++) {
		heights[i] = (short) getRandomNumber(1, columnBoxNumbers);
		marked[i] = (bool*) malloc(sizeof(bool) * columnBoxNumbers);
		for (j=0; j<columnBoxNumbers; j++) {
			marked[i][j] = false;
		}
	}
	
	for (i=0; i<maxClosuresNumber; i++) {
		closures[i].closure = NULL;
		closures[i].closureCount = 0;
		closures[i].closureColor = DARK;
	}
}

void setScreenColors() {
	short i, j;
	colors = (Color**) malloc(sizeof(Color*) * rowBoxNumbers);
	for (i=0; i<rowBoxNumbers; i++) {
		colors[i] = (Color*) malloc(sizeof(Color) * columnBoxNumbers);
	}

	for (i=0; i<rowBoxNumbers; i++) {
		for (j=0; j<heights[i]; j++) {
			colors[i][j] = (Color) getRandomNumber(PURPLE, BLUE);
		}
		
		for (j=heights[i]; j<columnBoxNumbers; j++) {
			colors[i][j] = DARK;
		}
	}
}

pair<short, short>* nextHorizontalClosure(short *&heights, 
										  Color **&colors, 
										  short &closureCount, 
										  bool **&marked) {
	short i, j, k, column, minHeight;
	Color pointColor;
	pair<short, short>* result = (pair<short, short>*) malloc(sizeof(pair<short, short>) * (rowBoxNumbers + columnBoxNumbers));
	bool found = false;
	for (i=0; i<rowBoxNumbers-1; i++) {
		if (i+closureMinVal > rowBoxNumbers)
			continue;
		
		minHeight = heights[i];
		for (k=i+1; k<i+closureMinVal && k<rowBoxNumbers; k++)
			if (heights[k] < minHeight) {
				minHeight = heights[k];
			}
		
		for (j=0; j<minHeight; j++) {
			if (marked[i][j])
				continue;
				
			pointColor = colors[i][j];
			column = i+1;
			closureCount = 1;
			while (column<rowBoxNumbers && colors[column][j] == pointColor) {
				closureCount++;
				column++;
			}
			
			if (closureCount >= closureMinVal) {
				found = true;
				break;
			}
		}
		
		if (found)
			break;
	}
	
	k = 0;
	if (found) {	
		for (i=column-closureCount; i<column; i++) {
			result[k] = pair<short, short>(i, j);
			marked[i][j] = true;
			k++;
		}
	} else {
		closureCount = 0;
	}
		
	while (k < rowBoxNumbers + columnBoxNumbers) {
		result[k] = pair<short, short>(-1, -1);
		k++;
	}
	
	return result;
}

pair<short, short>* nextVerticalClosure(short *&heights, 
										Color **&colors,
										short &closureCount,
										bool **&marked) {
	short i, j, k, row;
	Color pointColor;
	pair<short, short>* result = (pair<short, short>*) malloc(sizeof(pair<short, short>) * (rowBoxNumbers + columnBoxNumbers));
	bool found = false;
	for (i=0; i<columnBoxNumbers; i++) {
		for (j=0; j<heights[i]; j++) {
			if (marked[i][j])
				continue;
			
			if (j+closureMinVal>heights[i])
				break;
			
			closureCount = 1;
			pointColor = colors[i][j];
			row = j+1;
			while (row<columnBoxNumbers && colors[i][row] == pointColor) {
				closureCount++;
				row++;
			}

			if (closureCount >= closureMinVal) {
				found = true;
				break;
			}
		}
		
		if (found)
			break;
	}
	
	k = 0;
	if (found) {	
		for (j=row-closureCount; j<row; j++) {
			result[k] = pair<short, short>(i, j);
			marked[i][j] = true;
			k++;
		}
	} else {
		closureCount = 0;
	}

	while (k < rowBoxNumbers + columnBoxNumbers) {
		result[k] = pair<short, short>(-1, -1);
		k++;
	}
	
	return result;
}

void addUpDownClosure(pair<short, short> coord,
					  Color color,
					  short *heights,
					  Color **colors,
					  short &closureCount,
					  pair<short, short> *closure,
					  bool **&marked) {
	short i = coord.first, j;
	j = coord.second + 1;
	while (j < heights[i] && colors[i][j] == color) {
		if (marked[i][j]) {
			j++;
			continue;
		}
			
		closure[closureCount] = pair<short, short>(i, j);
		marked[i][j] = true;
		j++;
		closureCount++;
	}
	
	j = coord.second - 1;
	while (j >= 0 && colors[i][j] == color) {
		if (marked[i][j]) {
			j--;
			continue;
		}
			
		closure[closureCount] = pair<short, short>(i, j);
		marked[i][j] = true;
		j--;
		closureCount++;
	}
}

void addHorizontalCrossClosure(short *heights,
							   Color **colors,
							   short &closureCount,
							   pair<short, short> *closure,
							   bool **&marked) {
	if (!foundToVanish(closure)) 
		return;

	short iterator = 0, horizontalClosureCount = closureCount, i, j;
	pair<short, short> coord;
	Color color;
	
	do {
		coord = closure[iterator];
		color = colors[coord.first][coord.second];
		addUpDownClosure(coord, color, heights, colors, closureCount, closure, marked);
		iterator++;
	} while (iterator < horizontalClosureCount);
}

void addLeftRightClosure(pair<short, short> coord,
						 Color color,
						 Color **colors,
						 short &closureCount,
						 pair<short, short> *closure,
						 bool **&marked) {
	short i, j = coord.second;
	i = coord.first + 1;
	while (i < rowBoxNumbers && colors[i][j] == color) {
		if (marked[i][j]) {
			i++;
			continue;
		}
			
		closure[closureCount] = pair<short, short>(i, j);
		marked[i][j] = true;
		i++;
		closureCount++;
	}
	
	i = coord.first - 1;
	while (i >= 0 && colors[i][j] == color) {
		if (marked[i][j]) {
			i--;
			continue;
		}
			
			
		closure[closureCount] = pair<short, short>(i, j);
		marked[i][j] = true;
		i--;
		closureCount++;
	}
}

void addVerticalCrossClosure(short *heights, Color **colors, short &closureCount, pair<short, short> *closure, bool **&marked) {
	if (!foundToVanish(closure))
		return;
	
	short iterator = 0, verticalClosureCount = closureCount, i, j;
	pair<short, short> coord;
	Color color;
	
	do {
		coord = closure[iterator];
		color = colors[coord.first][coord.second];
		addLeftRightClosure(coord, color, colors, closureCount, closure, marked);
		iterator++;
	} while (iterator < verticalClosureCount);
}

void addCrossClosure(short *heights, Color **colors, short &closureCount, pair<short, short> *closure, bool **&marked, bool horizontalIsPrior=true) {
	bool checkHorizon = horizontalIsPrior;
	short currentCount;
	do {
		currentCount = closureCount;
		if (checkHorizon) {
			addHorizontalCrossClosure(heights, colors, closureCount, closure, marked);
		} else {
			addVerticalCrossClosure(heights, colors, closureCount, closure, marked);
		}
		
		checkHorizon = !checkHorizon;
	} while (currentCount != closureCount);
}

pair<short, short>* nextClosure(short *&heights, Color **&colors, bool **&marked, short &closureCount, bool horizontalIsPrior=true) {
	pair<short, short> *closure = NULL;
	closureCount = 0;
	if (horizontalIsPrior) {
		closure = nextHorizontalClosure(heights, colors, closureCount, marked);
	} else {
		closure = nextVerticalClosure(heights, colors, closureCount, marked);
	}
	
	addCrossClosure(heights, colors, closureCount, closure, marked, horizontalIsPrior);
	return closure;
}

void allClosures() {
	short i = 0, closureCount;
	
	// Appends all hoirzontal closures
	do {
		pair<short, short> *coords = nextClosure(heights, colors, marked, closureCount);
		if (!foundToVanish(coords))
			break;
		
		closures[i].closure = coords;
		closures[i].closureColor = colors[coords[0].first][coords[0].second];
		closures[i].closureCount = closureCount;
		i++;
	} while (i < maxClosuresNumber);
	
	// Appends all vertical closures
	do {
		pair<short, short> *coords = nextClosure(heights, colors, marked, closureCount, false);
		if (!foundToVanish(coords))
			break;
		
		closures[i].closure = coords;
		closures[i].closureColor = colors[coords[0].first][coords[0].second];
		closures[i].closureCount = closureCount;
		i++;
	} while (i < maxClosuresNumber);
}

short getNumberOfClosures() {
	short i = 0;
	while (closures[i++].closureColor != DARK);	
	return i-1;
}

short getColorScore(Color color) {

	switch (color) {
		case PURPLE:
			return purpleScore;
			
		case YELLOW:
			return yellowScore;
			
		case RED:
			return redScore;
		
		case GREEN:
			return greenScore;
			
		case BLUE:
			return blueScore;
			
		case DARK:
			return darkScore;
			
		default:
			return zero;
	}
}

void clearClosure(ClosureHolder *chPtr) {
	short ccnt = chPtr->closureCount;
	chPtr->closureColor = DARK;
	if (!ccnt)
		return;
		
	for (short idx = 0; idx < ccnt; idx++) {
		(chPtr->closure[idx]).first = (chPtr->closure[idx]).second = 0;
	}
	
	chPtr->closureCount = 0;
}

void clearClosures() {
	short nc = getNumberOfClosures(), idx = 0;
	while (idx < nc) {
		clearClosure(closures + idx);
		idx++;
	}
}

void disentangleClosure(ClosureHolder *chPtr) {
	free(chPtr->closure);
	chPtr->closure = NULL;
}

void disentangleClosures() {
	short idx = getNumberOfClosures();
	if (!idx)
		return;
		
	do {
		idx--;
		disentangleClosure(closures + idx);
	} while (idx);
}

bool dropAboveCells(short rwIdx, short clIdx) {
	if (!marked[clIdx][rwIdx])
		return false;
		
	short hght = heights[clIdx], idx = rwIdx;
	while (idx++ < hght) {
		if (idx == columnBoxNumbers)
			break;
			
		colors[clIdx][idx-1] = colors[clIdx][idx];
		marked[clIdx][idx-1] = marked[clIdx][idx];
	}
	
	if (idx == columnBoxNumbers) {
		colors[clIdx][idx-1] = DARK;
		marked[clIdx][idx-1] = false;
	}
	
	heights[clIdx] = --hght;
	colors[clIdx][hght] = DARK;
	marked[clIdx][hght] = false;
	return true;
}

void dropMarkedCells(short clIdx) {
	short rwIdx = 0, hght = heights[clIdx];
	while (rwIdx < hght) {
		if (!dropAboveCells(rwIdx, clIdx)) {
			rwIdx++;
		}
	}
}

void vanishMarkedOnBoard() {
	for (short clIdx = 0; clIdx < rowBoxNumbers; clIdx++) {
		dropMarkedCells(clIdx);
	}
}

#endif
