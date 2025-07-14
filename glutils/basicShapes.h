#ifndef __BASICSHAPES__
#define __BASICSHAPES__
#include <chrono>
#include <gl/gl.h>
#include "../calculationUtils/coordUtils.h"
#include "libUtils.h"

void setColorTripleBases(Color color, float &rColor, float &gColor, float &bColor) {
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
			
		case WHITE:
			rColor = whiteR; gColor = whiteG; bColor = whiteB;
			break;
			
		default:
			rColor = whiteR; bColor = whiteG; gColor = whiteB;
			break;
	}
}

// todo: use WINGDIAPI void APIENTRY glDrawPixels(GLsizei width,GLsizei height,GLenum format,GLenum type,const GLvoid *pixels); void drawBoxPixels();
void drawBox(short x, short y, float rColor, float gColor, float bColor) {
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

	// a12o: explict thread creation for customSwapBuffer as rendering_thread and screenlayout as manipulator_thread. Go on in a void function(void) 
	// with consumed global variables, within a busy loop. Though this way was not applied as a solution at last.
	while (i < times) {

		drawClosuresOff(closures, count);
		this_thread::sleep_for(chrono::milliseconds(blinkDuration));
		SwapBuffers(*globalHDCPtr);
		
		drawClosuresOn(closures, count);
		this_thread::sleep_for(chrono::milliseconds(blinkDuration));
		SwapBuffers(*globalHDCPtr);
		
		i++;
	}
	
	readyToVanish = true;
}

void drawTriangle(Color color, float vx1, float vx2, float vx3, float vy1, float vy2, float vy3) {
	float rc, gc, bc;
	setColorTripleBases(color, rc, gc, bc);
	glPushMatrix();
	glBegin (GL_TRIANGLES);
	glColor3f(rc, gc, bc); glVertex2f(vx1, vy1);
	glColor3f(rc, gc, bc); glVertex2f(vx2, vy2);
	glColor3f(rc, gc, bc); glVertex2f(vx3, vy3);
	glEnd ();
	glPopMatrix();
	customSwapBuffers();
}

void showWinningSign(Color color) {
	float vx1, vx2, vx3, vy1, vy2, vy3;
	setUpTriangleCoords(vx1, vx2, vx3, vy1, vy2, vy3);
	drawTriangle(color, vx1, vx2, vx3, vy1, vy2, vy3);
}

void showLossSign(Color color) {
	float vx1, vx2, vx3, vy1, vy2, vy3;
	setUpsideTriangleCoords(vx1, vx2, vx3, vy1, vy2, vy3);
	drawTriangle(color, vx1, vx2, vx3, vy1, vy2, vy3);
}

void drawRect(float rrx1, float rry1, float rrx2, float rry2, float rc, float gc, float bc) {
	// todo: impl
}

void draw_ld_Rbbr(float vx1, float vy1, float rc, float gc, float bc) {
	// todo : impl
}

void draw_lu_Rbbr(float vx1, float vy2, float rc, float gc, float bc) {
	// todo : impl
}

void draw_rd_Rbbr(float vx2, float vy1, float rc, float gc, float bc) {
	// todo : impl
}

void draw_ru_Rbbr(float vx2, float vy2, float rc, float gc, float bc) {
	// todo : impl
}

void drawLeftRbbr(float vx1, float vy1, float vx2, float rc, float gc, float bc) {
	// todo : impl
}

void drawRightRbbr(float vx2, float vy1, float vy2, float rc, float gc, float bc) {
	// todo : impl
}

// A binary rubber for substituting its inside elements. X & Y are relatively cell coordinations of the left box inside rubber
void drawRubber(short x, short y, Color color) {
	// todo : impl
}


#endif
