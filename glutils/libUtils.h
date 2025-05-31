#ifndef __LIBUTILS__
#define __LIBUTILS__

/**************************
 * Includes
 *
 **************************/

#include <chrono>
using namespace std;

#include <condition_variable>
#include <gl/gl.h>
#include <mutex>
using namespace std;

#include <thread>
using namespace std;

#include <windows.h>
#include <sched.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <tlhelp32.h>
#include <iostream>

#include "../constants/numbers.h"
#include "../constants/types.h"

/**************************
 * Function Declarations
 *
 **************************/

condition_variable cond_var;
mutex mtx;
unique_lock<mutex> unqlck{mtx};
HDC *globalHDCPtr;

Color **colors;
short *heights, renderCount = 0, numberOfClosures;
bool **marked;
ClosureHolder *closures;
BOOL bQuit;
MSG msg;

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

/************************************************************************
 * Platform angostically forces current process avoid creating additional 
 * threads and processor affinity
 *
 ************************************************************************/
bool force_single_thread() {
	#ifdef _WIN32
	DWORD mask = 1;		// Use only the first core
	if (SetProcessAffinityMask(GetCurrentProcess(), mask) == 0) {
		// Handle error
		return false;
	}
	#else
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	pthread_t current_thread = pthread_self();
	if (pthread_setaffinity_np(current_thread, 
			sizeof(cpu_set_t), &cpuset) != 0) {
		// Handle error, it could be EPERM which means the calling thread 
		// does not have the appropriate permission.
		return false;	
	}
	
	#endif
	return true;	
}

int getNumberOfThreads() {
    int count = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return -1; // Error
    }

    THREADENTRY32 te;
    te.dwSize = sizeof(te);
    if (!Thread32First(hSnapshot, &te)) {
        CloseHandle(hSnapshot);
        return -1; // Error
    }

    DWORD currentProcessId = GetCurrentProcessId();
    do {
        if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + 
				sizeof(te.th32OwnerProcessID)) {
            if (te.th32OwnerProcessID == currentProcessId) {
                count++;
            }
        }
        te.dwSize = sizeof(te);
    } while (Thread32Next(hSnapshot, &te));

    CloseHandle(hSnapshot);
    return count;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	    case WM_CREATE:
	        return 0;
	    case WM_CLOSE:
	        PostQuitMessage (0);
	        return 0;
	
	    case WM_DESTROY:
	        return 0;
	
	    case WM_KEYDOWN:
	        switch (wParam)
	        {
		        case VK_ESCAPE:
		            PostQuitMessage(0);
		            return 0;
	        }
	        
	        return 0;
	
	    default:
	        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{		
	PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
		
    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    globalHDCPtr = hDC;
	*hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );	
}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

void customFlush() {
	glFlush();
	glFinish();
}

void customSwapBuffers() {
	// refer the following link inorder to do this function synchronously
	// https://chrizog.com/cpp-thread-synchronization#:~:text=With%20C%2B%2B%20threads%20this%20can,function%20on%20the%20condition%20variable.
	// try to get result by manipulating customFlush
	// if not, try the third (future) solution. Although this way turns out as 
	// an async approach; It needs to make callable parameters global and use
	// creating threads on void function (void) as well.
	unique_lock<mutex> lock{mtx};
	cond_var.wait(lock, [](){		
		return SwapBuffers(*globalHDCPtr);
	});
		
	unqlck.unlock();
}

#endif
