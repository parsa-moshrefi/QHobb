#ifndef __COORDUTILS__
#define __COORDUTILS__
#include "../constants/numbers.h"
#include "../constants/types.h"
#include "../glutils/libUtils.h"

void calculateCoords(short x, short y, float &vx1, float &vx2, float &vy1, float &vy2) {
	short xCoeff = x - (rowBoxNumbers / 2);
	short yCoeff = y - (columnBoxNumbers / 2);
	vx1 = xCoeff * (sideHorizontalLength + rubberHThickness);
	vy1 = yCoeff * (sideVerticalLength + rubberVThickness);
	vx2 = xCoeff * (sideHorizontalLength + rubberHThickness) + sideHorizontalLength;
	vy2 = yCoeff * (sideVerticalLength + rubberVThickness) + sideVerticalLength;
}

void setUpTriangleCoords(float &vx1, float &vx2, float &vx3, float &vy1, float &vy2, float &vy3) {
	vx1 = -(columnBoxNumbers/8) * (sideHorizontalLength + rubberHThickness);
	vx2 = -vx1;
	vx3 = 0.0f;
	vy1 = vy2 = -(rowBoxNumbers/8) * (sideVerticalLength + rubberHThickness);
	vy3 = -vy1;
}

void setUpsideTriangleCoords(float &vx1, float &vx2, float &vx3, float &vy1, float &vy2, float &vy3) {
	vx1 = -(columnBoxNumbers/8) * (sideHorizontalLength + rubberHThickness);
	vx2 = -vx1;
	vx3 = 0.0f;
	vy1 = vy2 = (rowBoxNumbers/8) * (sideVerticalLength + rubberHThickness);
	vy3 = -vy1;
}

// Written in order to use with glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
pair<float, float> getOrigin() {
	float ox = -(rowBoxNumbers/2) * (sideHorizontalLength+rubberHThickness);
	float oy = -(columnBoxNumbers/2) * (sideVerticalLength+rubberVThickness);
	return pair<float, float>(ox, oy);
}

bool darkFilled(pair<short, short> coord) {
	if (coord.first == -1 || coord.second == -1)
		return true;
	
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

short min(short a, short b) {
	return (a < b) ? a : b;
}

short max(short a, short b) {
	return (a > b) ? a : b;
}

/***************************************************************************************************************
 * In the next 6 functions rs[x|y][1|2] are rubber segment x or y pixel coordination of two diameter endpoints *
 ***************************************************************************************************************/

void coords_ld_Rbbr(short x, short y, float& rsx1, float &rsy1, float &rsx2, float &rsy2) {
	// todo: impl
}

void coords_lu_Rbbr(short , short y, float &rsx1, float &rsy1, float &rsx2, float &rsy2) {
	// todo: impl
}

void coords_rd_Rbbr(short x, short y, float &rsx1, float &rsy1, float &rsx2, float &rsy2)  {
	// todo: impl
}

void coords_ru_Rbbr(short x, short y, float &rsx1, float &rsy1, float &rsx2, float &rsy2) {
	// todo: impl
}

void coordsLeftRbbr(short x, short y, float &rsx1, float rsy1, float &rsx2, float &rsy2) {
	// todo: impl
}

void coordsRightRbbr(short x, short y, float &rsx1, float &rsy1, float &rsx2, float &rsy2) {
	// todo: impl
}

#endif
