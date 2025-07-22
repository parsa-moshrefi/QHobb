#ifndef __COORDUTILS__
#define __COORDUTILS__
#include "../constants/numbers.h"
#include "../constants/types.h"
#include "../glutils/libUtils.h"

void calculateCoords(short x, short y, float &vx1, float &vx2, float &vy1, float &vy2) {
	short xCoeff = x - (rowBoxNumbers / 2);
	short yCoeff = y - (columnBoxNumbers / 2);
	vx1 = xCoeff * (sideHorizontalLength + rubberHThickness);
	vy1 = yCoeff * (sideVerticalLength + rubberVThickness) + nrwVCoeff * rubberVThickness;
	vx2 = vx1 + sideHorizontalLength;
	vy2 = vy1 + sideVerticalLength;
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

/**
 * Sets coordinates of left and down extra piece of rubber
 */
void coords_ld_Rbbr(float vx1, float vy1, float& rrx1, float &rry1, float &rrx2, float &rry2) {
	rrx1 = vx1 - hbrr - rubberHThickness * nrwHCoeff;
	rry1 = vy1 - vbrr - rubberVThickness * nrwVCoeff;
	rrx2 = vx1 + exCoeff * rubberHThickness;
	rry2 = vy1 - vbrr;
}

/**
 * Sets coordinates of left and up extra piece of rubber
 */
void coords_lu_Rbbr(float vx1, float vy2, float &rrx1, float &rry1, float &rrx2, float &rry2) {
	rrx1 = vx1 - hbrr - rubberHThickness * nrwHCoeff;
	rry1 = vy2 + vbrr;
	rrx2 = vx1 + exCoeff * rubberHThickness;
	rry2 = vy2 + vbrr + rubberVThickness * nrwVCoeff;
}

/**
 * Sets coordinates of rught and down extra piece of rubber
 */
void coords_rd_Rbbr(float vx2, float vy1, float &rrx1, float &rry1, float &rrx2, float &rry2)  {
	rrx1 = vx2 - exCoeff * rubberHThickness;
	rry1 = vy1 - vbrr - rubberVThickness * nrwVCoeff;
	rrx2 = vx2 + hbrr + rubberHThickness * nrwHCoeff;
	rry2 = vy1 - vbrr;
}

/**
 * Sets coordinates of right and up extra piece of rubber
 */
void coords_ru_Rbbr(float vx2, float vy2, float &rrx1, float &rry1, float &rrx2, float &rry2) {
	rrx1 = vx2 - exCoeff * rubberHThickness;
	rry1 = vy2 + vbrr;
	rrx2 = vx2 + hbrr + rubberHThickness * nrwHCoeff;
	rry2 = vy2 + vbrr + rubberVThickness * nrwVCoeff;
}

/**
 * Sets coordinates of left side of the rubber
 */
void coordsLeftRbbr(float vx1, float vy1, float vy2, float &rrx1, float& rry1, float &rrx2, float &rry2) {
	rrx1 = vx1 - hbrr - rubberHThickness * nrwHCoeff;
	rry1 = vy1 - vbrr;
	rrx2 = vx1 - hbrr;
	rry2 = vy2 + vbrr;
}

/**
 * Sets coordinates of right side of the rubber
 */
void coordsRightRbbr(float vx2, float vy1, float vy2, float &rrx1, float &rry1, float &rrx2, float &rry2) {	
	rrx1 = vx2 + hbrr;
	rry1 = vy1 - vbrr;
	rrx2 = vx2 + hbrr + rubberHThickness * nrwHCoeff;
	rry2 = vy2 + vbrr;
}

#endif
