/*------------------------------------------------------------
	lab1-helloworld.h 
	- Header file for Lab1.c
	
	Author: Tom Nightingale, based off example by 
			Charles Petzold, 1998

	Questions:
	3) Why should you call BeginPaint() in WM_PAINT msg? For 
	example what would happen if your code contained a WM_PAINT 
	case that contained only the code “return 0”? Explain WHY 
	this occurs.

	An important feature of BeginPaint() is to validate the 
	window. If BeginPaint() is not called, the window remains
	"dirty" or invalid and the operating system will keep 
	calling WM_PAINT cases to try validate the window.

	4) Why in the msg loop do you get a msg from the msg queue 
	then send it back to the O/S? Why don’t you just process 
	it yourself (call your wndproc())?

	We send it back to the O/S so that the O/S can then 
	provide the correct WinProc for us. This saves us from 
	having to try and find our specific window's WinProc.
  ------------------------------------------------------------*/

#ifndef LAB1_HELLOWORLD_H /* Convention is file name with '.' replaced by underscores. */
#define LAB1_HELLOWORLD_H

typedef struct _wdata_ {
	LPCWSTR text;
} wdata;

#endif