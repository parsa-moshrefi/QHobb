#include <omp.h>
#include "constants/literals.h"
#include "glutils/windowUtil.h"
#include "screen/screenLayout.h"

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    bQuit = FALSE;
	
	/* set number of threads on omp; Although opengl internally creates additional threads. */
	char ompEnv[] = "OMP_NUM_THREADS=1";
	putenv(ompEnv);
	registerWindow(wc, hInstance);

    /* create main window */    
    hWnd = CreateWindow (__lpClassName, __lpWindowName, WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, windowX, windowY, windowNWidth, windowNHeight, NULL, 
		NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
	initScreenVals();
	setScreenColors();
	renderScreen();
	
	/* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}
