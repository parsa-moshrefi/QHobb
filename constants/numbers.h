#ifndef __NUMBERS__
#define __NUMBERS__
#include <random>
#include <wingdi.h>
using namespace std;

enum Color { PURPLE = 1, YELLOW = 2, RED = 3, GREEN = 4, BLUE = 5, DARK = 6, WHITE = 7 };
enum DIRECTION { LEFT = 1, UP = 2, RIGHT = 3, DOWN = 4, NONE = 5 };

const short zero = 0;
const short windowX = 600;
const short windowY = 0;
const short windowNWidth = 768;
const short windowNHeight = 1024;
const short rowBoxNumbers = 8;
const short columnBoxNumbers = 12;
const short maxClosuresNumber = 10;
const short darkScore = 0;
const short purpleScore = 2;
const short yellowScore = 4;
const short redScore = 6;
const short greenScore = 8;
const short blueScore = 10;
const short closureMinVal = 3;
const short blinkTimes = 5;
const short blinkDuration = 200;
const short exCoeff = 2;	// extra part of the rubber based on times of vertical or horizontal thickness
const short initRbbrX = 0;	// initial x position place of the rubber
const short initRbbrY = 0;	// initial y position place of the rubber
const float initialTheta = 0.0f;
const float purpleR = 1.0f;
const float purpleG = 0.0f;
const float purpleB = 1.0f;
const float yellowR = 1.0f;
const float yellowG = 1.0f;
const float yellowB = 0.0f;
const float redR = 1.0f;
const float redG = 0.0f;
const float redB = 0.0f;
const float greenR = 0.0f;
const float greenG = 1.0f;
const float greenB = 0.0f;
const float blueR = 0.0f;
const float blueG = 0.0f;
const float blueB = 1.0f;
const float darkR = 0.0f;
const float darkG = 0.0f;
const float darkB = 0.0f;
const float whiteR = 1.0f;
const float whiteG = 1.0f;
const float whiteB = 1.0f;
const float rubberHThickness = 0.04f;
const float sideVerticalLength = 0.145f;
const float rubberVThickness = 0.02f;
const float sideHorizontalLength = 0.205f;
const float scorePerBoxVanish = 5.0f;
const float winScore = 300.0f;
const float vbrr = 0.01f;		// vertical distance between rubber and rectangle
const float hbrr = 0.005f;		// horizontal distance between rubber and rectangle
const float nrwHCoeff = 0.25f;	// coefficient for horizontal narrowing the thickness
const float nrwVCoeff = 0.25f;	// coefficient for vertical narrowing the thickness
const unsigned int winningScore = 100;
const UINT swapFlag = WGL_SWAP_MAIN_PLANE | WGL_SWAP_OVERLAY1 | WGL_SWAP_OVERLAY2 |	WGL_SWAP_OVERLAY3 | WGL_SWAP_OVERLAY4 | WGL_SWAP_OVERLAY5 |
	WGL_SWAP_OVERLAY6 | WGL_SWAP_OVERLAY7 | WGL_SWAP_OVERLAY8 |	WGL_SWAP_OVERLAY9 | WGL_SWAP_OVERLAY10 | WGL_SWAP_OVERLAY11 | WGL_SWAP_OVERLAY12 | 
	WGL_SWAP_OVERLAY13 | WGL_SWAP_OVERLAY14 | WGL_SWAP_OVERLAY15 | WGL_SWAP_UNDERLAY1 | WGL_SWAP_UNDERLAY2 | WGL_SWAP_UNDERLAY3 | WGL_SWAP_UNDERLAY4 | 
	WGL_SWAP_UNDERLAY5 | WGL_SWAP_UNDERLAY6 | WGL_SWAP_UNDERLAY7 | WGL_SWAP_UNDERLAY8 |	WGL_SWAP_UNDERLAY9 | WGL_SWAP_UNDERLAY10 | 
	WGL_SWAP_UNDERLAY11 | WGL_SWAP_UNDERLAY12 | WGL_SWAP_UNDERLAY13 | WGL_SWAP_UNDERLAY14 |	WGL_SWAP_UNDERLAY15;

const Color rubberColor = WHITE;
const UINT amsg1 = 257;
const UINT amsg2 = 256;
const UINT wsMsg1 = 257;
const UINT wsMsg2 = 256;
const UINT wsMsg3 = 258;
const WPARAM lawParam = 37;
const WPARAM uawParam = 38;
const WPARAM rawParam = 39;
const WPARAM dawParam = 40;
const WPARAM wswParam = 32;

int getRandomNumber(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);
	int randomValue = distrib(gen);
	return randomValue;
}

#endif
