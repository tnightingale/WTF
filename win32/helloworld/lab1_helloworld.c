/*------------------------------------------------------------
	lab1_helloworld.c 
	- Displays the words "Hello" and "World" in two 
				seperate windows.
	Author: Tom Nightingale, based on an example by 
			Charles Petzold, 1998
  ------------------------------------------------------------*/

#include <windows.h>
#include "lab1_helloworld.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Hello Tom, you are awesome!") ;
     HWND hwnd ;
     MSG msg ;
     WNDCLASS wndclass ;
	 wdata *data;
	 int win_x, win_y, win_w, win_h;

	 data = (wdata*) malloc(sizeof(wdata));
	 win_x = 100;
	 win_y = 100;
	 win_w = 400;
	 win_h = 100;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = sizeof(wdata);
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;     // loads an icon
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;         // loads a cursor
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;// Gets an object (a brush)
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), // displays a message box
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     // creates a window
     hwnd = CreateWindow (szAppName,                  // window class name
                          TEXT ("Window 1"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          win_x, //CW_USEDEFAULT,              // initial x position
                          win_y, //CW_USEDEFAULT,              // initial y position
                          win_w, //CW_USEDEFAULT,              // initial x size
                          win_h, //CW_USEDEFAULT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters

	 data->text = TEXT("Hello");
	 SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG) data);

     // shows the specified window
     ShowWindow (hwnd, iCmdShow) ;
     //updates the window (paints itself if "dirty"
     UpdateWindow (hwnd) ;
     
	 // creates a window
     hwnd = CreateWindow (szAppName,                  // window class name
                          TEXT ("Window 2"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          win_x + win_w, //CW_USEDEFAULT,              // initial x position
                          win_y, //CW_USEDEFAULT,              // initial y position
                          win_w, //CW_USEDEFAULT,              // initial x size
                          win_h, //CW_USEDEFAULT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters

	 data->text = TEXT("World");
	 SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG) data);

     // shows the specified window
     ShowWindow (hwnd, iCmdShow) ;
     //updates the window (paints itself if "dirty"
     UpdateWindow (hwnd) ;


     //get a message from the queue
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ; //Translate some keyboard messages 
          DispatchMessage (&msg) ;  //Sends the message to a windows procedure
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC hdc ;
     PAINTSTRUCT ps ;
     RECT rect ;
	 wdata *data;
     
     switch (message)
     {
     case WM_CREATE:
          PlaySound (TEXT ("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC) ; // plays a sound file
          return 0 ;
          
     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;    //specifies the start of a window paint
          
          GetClientRect (hwnd, &rect) ;     // gets the current size of the window
          
		  data = (wdata*) GetWindowLongPtr(hwnd, GWLP_USERDATA);

          DrawText (hdc, data->text, -1, &rect,    //displays a string
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
          
          EndPaint (hwnd, &ps) ;    //specifies the end of a window paint
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ; //adds a quit message into the message queue
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ; //default processing of messages
}