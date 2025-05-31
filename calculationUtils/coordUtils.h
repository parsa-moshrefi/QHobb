#ifndef __COORDUTILS__
#define __COORDUTILS__
#include "../constants/numbers.h"
#include "../constants/types.h"

void calculateCoords(short x, 
					 short y, 
					 float &vx1, 
					 float &vx2, 
					 float &vy1, 
					 float &vy2) {
	short xCoeff = x - (rowBoxNumbers / 2);
	short yCoeff = y - (columnBoxNumbers / 2);
	vx1 = xCoeff * (sideHorizontalLength + rubberHThickness);
	vy1 = yCoeff * (sideVerticalLength + rubberVThickness);
	vx2 = xCoeff * (sideHorizontalLength + rubberHThickness) + 
		sideHorizontalLength;
	vy2 = yCoeff * (sideVerticalLength + rubberVThickness) + 
		sideVerticalLength;	
}

// todo: In order to use with 
// glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
pair<float, float> getOrigin() {
	float ox = -(rowBoxNumbers/2) * (sideHorizontalLength+rubberHThickness);
	float oy = -(columnBoxNumbers/2) * (sideVerticalLength+rubberVThickness);
	return pair<float, float>(ox, oy);
}

bool darkFilled(pair<short, short> coord) {
	if (coord.first == -1 || coord.second == -1) {
		return true;
	}
	
	return false;
}

bool foundToVanish(pair<short, short>* coords) {
	for (short i=0; i<closureMinVal; i++) {
		if (darkFilled(coords[i]))
			return false;
	}
	
	return true;
}

void freeResources() {
	short i;
	for (i = 0; i<rowBoxNumbers; i++) {
		free(colors[i]);
		free(marked[i]);
	}
	
	free(heights);
	free(colors);
	free(marked);
	free(closures);
}

#endif
