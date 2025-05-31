#ifndef __BASICSHAPES__
#define __BASICSHAPES__
#include <chrono>
#include <gl/gl.h>
#include "../calculationUtils/coordUtils.h"
#include "libUtils.h"

void setColorTripleBases(Color color, 
						 float &rColor, 
						 float &gColor, 
						 float &bColor) {
	switch (color) {
		case PURPLE:
			rColor = purpleR; gColor = purpleG; bColor = purpleB;
			break;
		
		case YELLOW:
			rColor = yellowR; gColor = yellowG; bColor = yellowB;
			break;
			
		case RED:
			rColor = redR; gColor = redG; bColor = redB;
			break;
			
		case GREEN:
			rColor = greenR; gColor = greenG; bColor = greenB;
			break;
			
		case BLUE:
			rColor = blueR; gColor = blueG; bColor = blueB;
			break;
			
		case DARK:
			rColor = darkR; gColor = darkG; bColor = darkB;
			break;
			
		default:
			rColor = whiteR; bColor = whiteG; gColor = whiteB;
			break;
	}
}

// WINGDIAPI void APIENTRY glDrawPixels(GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid *pixels);
void drawBoxPixels(/*todo: parameters*/);

void drawBox(short x, 
			 short y, 
			 float rColor, 
			 float gColor, 
			 float bColor) {
	float vx1, vx2, vy1, vy2;
	calculateCoords(x, y, vx1, vx2, vy1, vy2);
	glPushMatrix ();
    glBegin (GL_QUADS);
    glColor3f (rColor, gColor, bColor);	glVertex2f (vx1, vy1);
    glColor3f (rColor, gColor, bColor); glVertex2f (vx1, vy2);
    glColor3f (rColor, gColor, bColor); glVertex2f (vx2, vy2);
    glColor3f (rColor, gColor, bColor);	glVertex2f (vx2, vy1);
    glEnd ();
    glPopMatrix ();    
}

void drawBox(short x, short y, Color color) {
	float rColor, gColor, bColor;
	setColorTripleBases(color, rColor, gColor, bColor);
	drawBox(x, y, rColor, gColor, bColor);	
}

void blinkBox(short x, 
			  short y, 
			  Color color, 
			  bool &blinkDone, 
			  short times=blinkTimes) {
	short i = 0;
	while (i++ < times && !blinkDone) {
		drawBox(x, y, DARK);		
		this_thread::sleep_for(chrono::milliseconds(blinkDuration));
		customSwapBuffers();
		drawBox(x, y, color);
		this_thread::sleep_for(chrono::milliseconds(blinkDuration));
		customSwapBuffers();
	}
	
	blinkDone = true;
}

void drawCoords(pair<short, short> *&coords, short count, Color color) 
{
	for (short i=0; i<count; i++) {
		drawBox(coords[i].first, coords[i].second, color);
	}	
}

void drawClosureOn(ClosureHolder &holder) {	
	drawCoords(holder.closure, holder.closureCount, holder.closureColor);	
}

void drawClosureOff(ClosureHolder &holder) {
	drawCoords(holder.closure, holder.closureCount, DARK);	
}

void drawClosuresOn(ClosureHolder *&closures, short count) {
	for (short i=0; i<count; i++) {
		drawClosureOn(closures[i]);
	}
}

void drawClosuresOff(ClosureHolder *&closures, short count) {
	for (short i=0; i<count; i++) {
		drawClosureOff(closures[i]);
	}
}

void blinkClosures(short count,
				   short times=blinkTimes) {
	short i = 0;
	if (count == 0)
		return;

	// 1wtodo: explict thread creation for customSwapBuffer as rendering_thread
	// and screenlayout as manipulator_thread. Go on in a void function(void)
	// with consumed global variables, within a busy loop.
	while (i < times) {

		drawClosuresOff(closures, count);		
		this_thread::sleep_for(chrono::milliseconds(blinkDuration));
		SwapBuffers(*globalHDCPtr);
		
		drawClosuresOn(closures, count);
		this_thread::sleep_for(chrono::milliseconds(blinkDuration));
		SwapBuffers(*globalHDCPtr);
		
		i++;
	}
}

#endif
