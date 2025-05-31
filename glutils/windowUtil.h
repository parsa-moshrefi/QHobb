#ifndef __WINDOWUTIL__
#define __WINDOWUTIL__
#include "../constants/literals.h"
#include "libUtils.h"

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

#endif
