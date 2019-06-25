#include "stdafx.h" 
#include "draw2.h" 
#include <cstdio> 

#define MAX_LOADSTRING 100 

#define TMR_1 1 
#define TMR_2 2 
#define TMR_3 3 
#define TMR_4 4 
#define TMR_5 5 
// Global Variables: 
HINSTANCE hInst; // current instance 
TCHAR szTitle[MAX_LOADSTRING]; // The title bar text 
TCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name 
INT value, pietro;
INT t = 0;
INT poziom;
INT i = 0;
INT j = 0;
INT przywolanie[10][10];
// buttons 
HWND hwndButton;

//zakres rysowania 
RECT drawArea1 = { 0, 0, 300, 400 };//stare 
const RECT drawArea2 = { 402,27 , 199, 399 };

// Forward declarations of functions included in this code module: 
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Buttons(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Static(HWND, UINT, WPARAM, LPARAM);

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);//inicjalizacja 
	Pen pen(Color(255, 0, 0, 255));//kolor 

	graphics.DrawLine(&pen, 125, 125, 400, 125);//linia 
	graphics.DrawLine(&pen, 125, 225, 400, 225);//linia 
	graphics.DrawLine(&pen, 125, 325, 400, 325);//linia 
	graphics.DrawLine(&pen, 125, 425, 400, 425);//linia 
	graphics.DrawRectangle(&pen, 400, 25, 200, 400);//szyb windy 

	//graphics.DrawRectangle(&pen, 405, value, 190, value - 240); 
}
void WINDA(HDC hdc)
{
	Graphics graphics(hdc);//inicjalizacja 
	Pen pen(Color(255, 0, 0, 255));//kolor 
	graphics.DrawRectangle(&pen, 405, value, 190, 90);
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	//if (drawArea == NULL) 
	//InvalidateRect(hWnd, NULL, TRUE); // repaint all 
	//else 
	InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea 
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	WINDA(hdc);
	EndPaint(hWnd, &ps);
}

void repaintWinda(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	//if (drawArea == NULL) 
	//InvalidateRect(hWnd, NULL, TRUE); // repaint all 
	//else 
	InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea 
	hdc = BeginPaint(hWnd, &ps);
	WINDA(hdc);
	EndPaint(hWnd, &ps);
}

void zjazdnadol(HWND hWnd) {
	if (value == 330) {
		KillTimer(hWnd, TMR_3);

	}
	else {
		value++;
		if (value == 330)
			KillTimer(hWnd, TMR_3);

	}
}

void wktorastrone(HWND hWnd) {
	switch (przywolanie[0][0])
	{
	case 4:    if (value == 30)
	{
		pietro = przywolanie[1][0];
		SetTimer(hWnd, TMR_1, 25, 0);
	}
			   else
	{
		pietro = przywolanie[0][0];   SetTimer(hWnd, TMR_1, 25, 0);
	}
			   break;
	case 3:   if (value == 130) {
		pietro = przywolanie[1][0]; SetTimer(hWnd, TMR_1, 25, 0);
	}
			  else { pietro = przywolanie[0][0]; SetTimer(hWnd, TMR_1, 25, 0); }
			  break;
	case 2:   if (value == 230) {
		pietro = przywolanie[1][0]; SetTimer(hWnd, TMR_1, 25, 0);
	}
			  else { pietro = przywolanie[0][0];  SetTimer(hWnd, TMR_1, 25, 0); }
			  break;
	case 1:   if (value == 330) {
		pietro = przywolanie[1][0]; SetTimer(hWnd, TMR_1, 25, 0);
	}
			  else { pietro = przywolanie[0][0];  SetTimer(hWnd, TMR_1, 25, 0); }
			  break;
	default:   SetTimer(hWnd, TMR_3, 25, 0);
		break;
	}

}

void drugipostoj(HWND hWnd) {
	i = 0;
	j = 0;
	if (value == 330) {
		KillTimer(hWnd, TMR_4);
	}
	else {
		value++;
		if (value == 330)
			KillTimer(hWnd, TMR_4);
	}
}
void kolejnypostoj(HWND hWnd) {
	t++;
	if (t == 205) {
		t = 0;
		KillTimer(hWnd, TMR_3);
		SetTimer(hWnd, TMR_4, 25, 0);

	}
}
void ostatnipostoj(HWND hWnd) {
	t++;
	if (t == 205) {
		t = 0;
		KillTimer(hWnd, TMR_5);
		wktorastrone(hWnd);

	}
}
void zamiana(HWND hWnd) {
	for (int a = 0; a <= j; a++) {
		przywolanie[0][a] = przywolanie[0][a + 1];
		przywolanie[1][a] = przywolanie[1][a + 1];
	}
	j--;
	if (przywolanie[0][0] == 0)
	{
		SetTimer(hWnd, TMR_3, 25, 0);
	}
	else {
		SetTimer(hWnd, TMR_5, 25, 0);
	}
}

void postoj(HWND hWnd) {
	if (przywolanie[1][0] == 3 && value == 130 || przywolanie[1][0] == 4 && value == 30 || przywolanie[1][0] == 2 && value == 230 || przywolanie[1][0] == 1 && value == 330) {
		KillTimer(hWnd, TMR_2);
		zamiana(hWnd);
	}
	else {
		t++;
		if (t == 250) {
			t = 0;
			KillTimer(hWnd, TMR_2);
			wktorastrone(hWnd);

		}
	}

}
void pietra(HWND hWnd) {
	switch (pietro)
	{
	case 4:        if (value == 30) {
		KillTimer(hWnd, TMR_1);  SetTimer(hWnd, TMR_2, 12, 0);
	}
				   else {
		value--;
		if (value == 30) {
			KillTimer(hWnd, TMR_1);  SetTimer(hWnd, TMR_2, 12, 0);
		}
	}
				   break;

	case 3:        if (value == 130) {
		KillTimer(hWnd, TMR_1);
		SetTimer(hWnd, TMR_2, 25, 0);
	}
				   else {
		if (value > 130) {
			value--;
			if (value == 130) {
				KillTimer(hWnd, TMR_1);
				SetTimer(hWnd, TMR_2, 25, 0);
			}
		}
		else {
			value++;
			if (value == 130) {
				KillTimer(hWnd, TMR_1);
				SetTimer(hWnd, TMR_2, 25, 0);
			}
		}
	}

				   break;
	case 2:        if (value == 230) {
		KillTimer(hWnd, TMR_1); SetTimer(hWnd, TMR_2, 12, 0);
	}
				   else {
		if (value > 230) {
			value--;
			if (value == 230) {
				KillTimer(hWnd, TMR_1); SetTimer(hWnd, TMR_2, 12, 0);
			}
		}
		else {
			value++;
			if (value == 230) {
				KillTimer(hWnd, TMR_1); SetTimer(hWnd, TMR_2, 12, 0);
			}
		}
	}
				   break;
	case 1:if (value == 330) {
		KillTimer(hWnd, TMR_1);
		SetTimer(hWnd, TMR_2, 12, 0);
	}
		   else {
		value++;
		if (value == 330) {
			KillTimer(hWnd, TMR_1);
			SetTimer(hWnd, TMR_2, 12, 0);
		}
	}
		   break;

	default:   SetTimer(hWnd, TMR_3, 25, 0); KillTimer(hWnd, TMR_1);
		break;
	}


}



// main function (exe hInstance) 
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// TODO: Place code here. 
	MSG msg;
	HACCEL hAccelTable;
	value = 330;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings 
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Perform application initialization: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));
	// Main message loop: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}



// 
//  FUNCTION: MyRegisterClass() 
// 
//  PURPOSE: Registers the window class. 
// 
//  COMMENTS: 
// 
//    This function and its usage are only necessary if you want this code 
//    to be compatible with Win32 systems prior to the 'RegisterClassEx' 
//    function that was added to Windows 95. It is important to call this function 
//    so that the application will get 'well formed' small icons associated 
//    with it. 
// 
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_HIGHLIGHT + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

// 
//   FUNCTION: InitInstance(HINSTANCE, int) 
// 
//   PURPOSE: Saves instance handle and creates main window 
// 
//   COMMENTS: 
// 
//        In this function, we save the instance handle in a global variable and 
//        create and display the main program window. 
// 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd;
	hInst = hInstance; // Store instance handle (of exe) in our global variable 

	// main window--ROZMIARY 
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);


	// create button and store the handle                                                       
	//4PIETRO 
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("1"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 100,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON14,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);                               // extra bits you dont really need 
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("2"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 75,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON14,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("3"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 50,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON34,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	//3PIETRO 
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("1"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 200,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON13,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("2"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 175,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON23,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("4"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 150,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON43,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);

	//2PIETRO 
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("1"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 300,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON12,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("3"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 275,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON32,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("4"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 250,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON42,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	//1PIETRO 
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("2"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 400,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON21,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("3"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 375,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON31,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button 
		TEXT("4"),                  // the caption of the button 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles 
		125, 350,                                  // the left and top co-ordinates 
		25, 25,                              // width and height 
		hWnd,                                 // parent window handle 
		(HMENU)ID_BUTTON41,                   // the ID of your button 
		hInstance,                            // the instance of your application 
		NULL);



	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

// 
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM) 
// 
//  PURPOSE:  Processes messages for the main window. 
// 
//  WM_COMMAND - process the application menu 
//  WM_PAINT - Paint the main window (low priority) 
//  WM_DESTROY - post a quit message and return 
// 
// 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int k; //pocoto 

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);


		// MENU & BUTTON messages 
		// Parse the menu selections: 
		switch (wmId)
		{

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);

			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			//poziom4 
		case ID_BUTTON34:
			poziom = 4;
			przywolanie[i][j] = 4; i++;
			przywolanie[i][j] = 3; j++;
			i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON24:
			poziom = 4;
			przywolanie[i][j] = 4; i++;
			przywolanie[i][j] = 2; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON14:
			poziom = 4;
			przywolanie[i][j] = 4; i++;
			przywolanie[i][j] = 1; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
			//poziom3 
		case ID_BUTTON43:
			poziom = 3;
			przywolanie[i][j] = 3; i++;
			przywolanie[i][j] = 4; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON23:
			poziom = 3;
			przywolanie[i][j] = 3; i++;
			przywolanie[i][j] = 2; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON13:
			poziom = 3;
			przywolanie[i][j] = 3; i++;
			przywolanie[i][j] = 1; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
			//poziom2 
		case ID_BUTTON12:
			poziom = 2;
			przywolanie[i][j] = 2; i++;
			przywolanie[i][j] = 1; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON32:
			poziom = 2;
			przywolanie[i][j] = 2; i++;
			przywolanie[i][j] = 3; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON42:
			poziom = 2;
			przywolanie[i][j] = 2; i++;
			przywolanie[i][j] = 4; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
			//poziom1 
		case ID_BUTTON41:
			poziom = 1;
			przywolanie[i][j] = 1; i++;
			przywolanie[i][j] = 4; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON31:
			poziom = 1;
			przywolanie[i][j] = 1; i++;
			przywolanie[i][j] = 3; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;
		case ID_BUTTON21:
			poziom = 1;
			przywolanie[i][j] = 1; i++;
			przywolanie[i][j] = 2; j++; i = 0;
			if (j == 1) {
				wktorastrone(hWnd);
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); // tworzenie kontekstu urz¹dzenia HDC 

		// TODO: Add any drawing code here (not depend on timer, buttons) 
		repaintWindow(hWnd, hdc, ps, NULL);
		//repaintWinda(hWnd, hdc, ps, NULL); 
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:// ten komunikat bêdzie obs³u¿ony, gdy wciœniesz przycisk zamkniêcia programu 
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		//tutaj chyba podzial na rozne timery 
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint 
			pietra(hWnd);
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case TMR_2:
			postoj(hWnd);
			break;
		case TMR_4:
			drugipostoj(hWnd);
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case TMR_3:
			kolejnypostoj(hWnd);
			break;
		case TMR_5:
			ostatnipostoj(hWnd);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}






// Message handler for about box. 
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}