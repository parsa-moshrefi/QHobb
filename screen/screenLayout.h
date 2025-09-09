#ifndef __SCREENLAYOUT__
#define __SCREENLAYOUT__
#include "screenValues.h"
#include "../calculationUtils/score.h"
#include "../glutils/basicShapes.h"
#include "../glutils/libUtils.h"
#include "../glutils/windowUtil.h"
#include <list>
#include <utility>
using namespace std;

void drawScreenLayout() {
	float rColor, gColor, bColor;
	glClear(GL_COLOR_BUFFER_BIT);
	for (short i=0; i<rowBoxNumbers; i++) {
		for (short j=0; j<columnBoxNumbers; j++) {
			Color color = colors[i][j];
			drawBox(i, j, color);
		}		
	}
	
	drawRubber(WHITE);
	SwapBuffers(*globalHDCPtr);
	customFlush();
}

void clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(*globalHDCPtr);
	customFlush();
}

void checkShowResult() {
	if (finished = checkWinScore()) {
		glClear(GL_COLOR_BUFFER_BIT);
		showWinningSign(GREEN);			
	} else if (finished = checkLossCondition()) {
		glClear(GL_COLOR_BUFFER_BIT);
		showLossSign(RED);
	}
}

void vanishClosures() {
	short nc = getNumberOfClosures();
	if (nc) {
		clearClosures();
		disentangleClosures();
		vanishMarkedOnBoard();
	}

	readyToVanish = false;
}

void renderScreen() {
	while (!bQuit) {
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				bQuit = TRUE;
				freeResources();
	 		}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				kbQHBFunc();				
			}
		}
		else
		{	
			if (numberOfClosures = getNumberOfClosures())
				scoresUpdated = false;
			
			if (renderCount++ <= numberOfClosures || finished)
				continue;
				
			// Critical section in order to prevent extra threads simulataneously corrupts winGDI buffer
			otr_cond_var.wait(otrlck, []() {
				drawScreenLayout();
				allClosures();
				blinkClosures(numberOfClosures);
				updateTotalScore(numberOfClosures);				
				checkShowResult();
				doActions();
				clearKBStat();				
				return TRUE;	
			});
			
			if (readyToVanish) {
				vanishClosures();
				// todo: randomly append some boxes on the board.
			}
		}
	}
}

#endif
