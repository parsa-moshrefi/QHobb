#ifndef __SCREENLAYOUT__
#define __SCREENLAYOUT__
#include "screenValues.h"
#include "../glutils/basicShapes.h"
#include <list>
#include <utility>
using namespace std;

void drawScreenLayout() {
	float rColor, gColor, bColor;
	glClear(GL_COLOR_BUFFER_BIT);
	for (short i=0; i<rowBoxNumbers; i++) {
		for (short j=0; j<heights[i]; j++) {
			Color color = colors[i][j];
			drawBox(i, j, color);
		}		
	}
	
	SwapBuffers(*globalHDCPtr);
	customFlush();
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
			}
		}
		else
		{		
			numberOfClosures = getNumberOfClosures();
			if (renderCount++ <= numberOfClosures)
				continue;

			// Critical section in order to prevent extra threads 
			// simulataneously corrupts winGDI buffer
			cond_var.wait(unqlck, []() {
				drawScreenLayout();
				allClosures();					
				blinkClosures(numberOfClosures);
				return TRUE;
			});
			
			unqlck.unlock();
		}
	}
}

#endif
