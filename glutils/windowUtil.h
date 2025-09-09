#ifndef __WINDOWUTIL__
#define __WINDOWUTIL__
#include "../constants/literals.h"
#include "libUtils.h"
#include "../glutils/basicShapes.h"

void registerWindow(WNDCLASS& wc, HINSTANCE& hInstance) {
	/* register window class */
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = zero;
	wc.cbWndExtra = zero;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = __lpClassName;
	RegisterClass(&wc);
}

void checkDirection(MSG &msg) {
	rubberMoved = true;
	
	if (msg.message != amsg1) {
		direction = NONE;
		rubberMoved = false;
		return;
	}
	
	switch (msg.wParam) {
		case lawParam:
			direction = LEFT;
			break;
			
		case uawParam:
			direction = UP;
			break;

		case rawParam:
			direction = RIGHT;
			break;
			
		case dawParam:
			direction = DOWN;
			break;
			
		default:
			direction = NONE;
			rubberMoved = false;
			break;
	}
}

void checkSwap(MSG &msg) {
	if (msg.message != wsMsg1) {
		doSwap = false;
		return;
	}
	
	if (msg.wParam == wswParam) {
		doSwap = true;
	}
}

void kbQHBFunc() {
	checkDirection(msg);
	checkSwap(msg);
}

void clearKBStat() {
	direction = NONE;
	doSwap = false;
	rubberMoved = false;
}

void moveLeft() {
	if (rbbrx <= 0)
		return;
		
	rbbrx--;
	direction = NONE;
}

void moveUp() {
	if (rbbry >= columnBoxNumbers - 1)
		return;
		
	rbbry++;
	direction = NONE;
}

void moveRight() {
	if (rbbrx >= rowBoxNumbers - 2)
		return;
		
	rbbrx++;
	direction = NONE;
}

void moveDown() {
	if (rbbry <= 0)
		return;
		
	rbbry--;
	direction = NONE;
}

void moveRubber() {
	if (direction == NONE)
		return;
	
	eraseRubber();
	switch (direction) {
		case LEFT:
			moveLeft();
			break;
			
		case UP:
			moveUp();
			break;
			
		case RIGHT:
			moveRight();
			break;
			
		case DOWN:
			moveDown();
			break;
		
		default:
			break;
	}
}

bool checkSurrounding() {
	return rbbrx >= 0 && rbbrx <= rowBoxNumbers - 2 && rbbry >= 0 && rbbry <= columnBoxNumbers - 1;
}

bool checkDarkness() {
	return colors[rbbrx][rbbry] == DARK || colors[rbbrx + 1][rbbry] == DARK;
}

void swapRubberElems() {
	if (!doSwap || !checkSurrounding() || checkDarkness())
		return;
	
	Color left = colors[rbbrx][rbbry], right = colors[rbbrx + 1][rbbry];
	drawBox(rbbrx, rbbry, right);
	drawBox(rbbrx + 1, rbbry, left);
	colors[rbbrx + 1][rbbry] = left;
	colors[rbbrx][rbbry] = right;
}

void doActions() {
	moveRubber();
	swapRubberElems();
}

#endif
