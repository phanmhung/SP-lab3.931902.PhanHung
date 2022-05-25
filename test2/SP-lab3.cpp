#include "stdafx.h"
#include "lab3.h"
#include <windows.h>
#include <math.h>

#define NUM    1000
#define TWOPI  (2 * 3.14159)

#define MAX_LOADSTRING 100

// Global variables:
HINSTANCE hInst;                                // Pointer to the current request
WCHAR szTitle[MAX_LOADSTRING];                  // Text in header line
WCHAR szWindowClass[MAX_LOADSTRING];            // Main window class name

// Declaration of functions:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//Sinewave using Polyline
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST2));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    return RegisterClassExW(&wcex);
}

 //Store the query in a global variable
 //Create and display the main window of the program
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// Handling the message for the main window
// WM_COMMAND - Command processing
// WM_PAINT - Draws the main window
// WM_DESTROY - End and return

int	num_func = 0; //1-sin, 2-cos, 3-tan, 4-ctg

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static int  cxClient, cyClient;
	int         i;
	POINT       apt[NUM];

    switch (message)
    {
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	}

    case WM_COMMAND:
    {
		int wmId = LOWORD(wParam);
		// Analyze the selected item in the menu
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case ID_FUNCTIONS_SIN:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 1;
			UpdateWindow(hWnd);
			break;

		case ID_FUNCTIONS_COS:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 2;
			UpdateWindow(hWnd);
			break;

		case ID_FUNCTIONS_TAN:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 3;
			UpdateWindow(hWnd);
			break;

		case ID_FUNCTIONS_CTG:
			InvalidateRect(hWnd, NULL, TRUE);
			num_func = 4;
			UpdateWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
    }

	break;

    case WM_PAINT:
	{
		HDC hdc = BeginPaint(hWnd, &ps);

		// Drawing the selected function
		switch (num_func)
		{
		case 1:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);

			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
			}

			Polyline(hdc, apt, NUM);
			break;

		case 2:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);

			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - cos(TWOPI * i / NUM)));
			}

			Polyline(hdc, apt, NUM);
			break;

		case 3:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);

			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - tan(TWOPI * i / NUM)));
			}

			Polyline(hdc, apt, NUM);
			break;

		case 4:
			MoveToEx(hdc, 0, cyClient / 2, NULL);
			LineTo(hdc, cxClient, cyClient / 2);

			for (i = 0; i < NUM; i++)
			{
				apt[i].x = i * cxClient / NUM;
				apt[i].y = (int)(cyClient / 2 * (1 - 1 / tan(TWOPI * i / NUM)));
			}

			Polyline(hdc, apt, NUM);
			break;
		}

		EndPaint(hWnd, &ps);
		break;
	}

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}