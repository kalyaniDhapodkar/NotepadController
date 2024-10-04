
// Header Files
#include <Windows.h>
#include <stdlib.h>

#include "notepad.h"

#define IDM_SYS_ABOUT 	16

/*
	isytle - Button style
	szText - Button Text
*/
struct 
{
	int iStyle;
	TCHAR* szText;
}
button[] = 
{
	/* BUTTON 0 */ BS_PUSHBUTTON, TEXT("Hack Notepad"),
	/* BUTTON 1 */ BS_PUSHBUTTON, TEXT("Set To Initial Window"),
	/* BUTTON 2 */ BS_PUSHBUTTON, TEXT("Move Notepad Left"),
	/* BUTTON 3 */ BS_PUSHBUTTON, TEXT("Remove Menu"),
	/* BUTTON 4 */ BS_PUSHBUTTON, TEXT("Change Window Name"),

	/* BUTTON 5 */ BS_PUSHBUTTON, TEXT("Change Icon"),
	/* BUTTON 6 */ BS_PUSHBUTTON, TEXT("Move Notepad Up"),
	/* BUTTON 7 */ BS_PUSHBUTTON, TEXT("Move Window (5, 5, 500, 300)"),
	/* BUTTON 8 */ BS_PUSHBUTTON, TEXT("Move Notepad Down"),
	/* BUTTON 9 */ BS_PUSHBUTTON, TEXT("Add Text With Change Font"),

	/* BUTTON 10 */ BS_PUSHBUTTON, TEXT("Increase Horizontal Size"),
	/* BUTTON 11 */ BS_PUSHBUTTON, TEXT("Increase Vertical Size"),
	/* BUTTON 12 */ BS_PUSHBUTTON, TEXT("Move Notepad Right"),
	/* BUTTON 13 */ BS_PUSHBUTTON, TEXT("Decrease Horizontal Size"),
	/* BUTTON 14 */ BS_PUSHBUTTON, TEXT("Decrease Vertical Size"),

	/* BUTTON 15 */ BS_PUSHBUTTON, TEXT("Close Notepad"),
};


// Global Variable Declaration
HWND hNotepad = NULL;
HICON hIcon;
HICON hNotepadIcon;
HMENU hMenu;

RECT rcWndNotepad, rcWndNotepadClient, rcWndNotepadInitial, rcWndNotepadClientInitial;

TCHAR szNotepadWindowName[255] = TEXT("Untitled - Notepad");
TCHAR szAppName2[] = TEXT("About");

// Global Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam); 
BOOL CompareWindowsNames(TCHAR* str, TCHAR* szCharString);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	HMENU hMenu;
	MSG msg;
	TCHAR szAppName[] = TEXT("Kalyani");

	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// WNDCLASSEX Initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register WNDCLASSEX
	RegisterClassEx(&wndclass);

	// Crreating Window
	hwnd = CreateWindow(szAppName,
						TEXT("Kalyani Dhapodkar : Window"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						670,
						520,
						NULL,
						NULL,
						hInstance,
						NULL);

	hMenu = GetSystemMenu(hwnd, FALSE);

	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenu, MF_STRING, IDM_SYS_ABOUT, TEXT("About"));

	// Show Window
	ShowWindow(hwnd, iCmdShow);

	// Update Window
	UpdateWindow(hwnd);

	// Message Loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

/*
	Function Name - WndProc
	Description  -	* A Callback Function for any interaction with window handles the msgs
					* WM_CREATE - Creates button
					* WM_COMMAND - handles all the buttons
					* WM_DESTROY - Destroys the Parent Window
	INPUT PARAMETER - 	1. hwnd - handle of the window
						2. iMsg - message from message loop
						3. wParam - contains additional data/information
						4. lParam - contains additional long data/information
	RETURN -  return value is the result of the message processing 
			  A call provides default processing of the messages which are not handled
*/					

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Local Variable Declaration
	static HWND hwndButton[16];
	static int cxChar, cyChar; 
	short i;
	TCHAR str[255];

	// Code
	switch(iMsg)
	{
		// A create Procedure which will be called first and only once
		case WM_CREATE:
			cxChar = LOWORD(GetDialogBaseUnits()); // horizontal dialogbox base unit
			cyChar = HIWORD(GetDialogBaseUnits()); // vertical dialogbox base unit

			// First column of buttons
			for(i = 0; i < 5; i++)
				hwndButton[i] = CreateWindow(TEXT("button"),
											button[i].szText,
											WS_CHILD | WS_VISIBLE | button[i].iStyle,
											cxChar, 
											cyChar * (1+3*i),
											21 * cxChar, 
											7 * cyChar/4,
											hwnd, 
											(HMENU)i,
											NULL, 
											NULL);

			// second column of buttons
			for(i = 5; i < 10; i++)
				hwndButton[i] = CreateWindow(TEXT("button"),
											button[i].szText,
											WS_CHILD | WS_VISIBLE | button[i].iStyle,
											cxChar+200, 
											cyChar * (1+3*i-15),
											27 * cxChar, 
											7 * cyChar/4,
											hwnd, 
											(HMENU) i,
											NULL, 
											NULL);

			// third column of buttons
			for(i = 10; i < 15; i++)
				hwndButton[i] = CreateWindow(TEXT("button"),
											button[i].szText,
											WS_CHILD | WS_VISIBLE | button[i].iStyle,
											cxChar+450, 
											cyChar * (1+3*i-30),
											21 * cxChar, 
											7 * cyChar/4,
											hwnd, 
											(HMENU)i,
											NULL, 
											NULL);

			// close button
			hwndButton[15] = CreateWindow(TEXT("button"),
											button[15].szText,
											WS_CHILD | WS_VISIBLE | button[i].iStyle,
											cxChar, 
											cyChar * (1+3*i-30),
											78 * cxChar, 
											48 * cyChar/4,
											hwnd, 
											(HMENU)15,
											NULL, 
											NULL);
			break;

		// Handling the messages / button interactions
		case WM_COMMAND:

			switch(LOWORD(wParam))
			{
				// Button - HackNotepad
				case 0 :
					if(hNotepad == NULL)
					{
						EnumWindows(EnumWindowsProc, lParam);
						GetWindowRect(hNotepad, &rcWndNotepad);
						GetClientRect(hNotepad, &rcWndNotepadClient);

						rcWndNotepadInitial.left = rcWndNotepad.left;
						rcWndNotepadInitial.top = rcWndNotepad.top;
						rcWndNotepadClientInitial.right = rcWndNotepadClient.right;
						rcWndNotepadClientInitial.bottom = rcWndNotepadClient.bottom;
						hMenu = GetMenu(hNotepad);
						wsprintf(str, TEXT("Notepad Hacked"));
						MessageBox(hwnd, str, TEXT("Message"), MB_OK);
					}
					break;

				// Button - Set to Initial Window
				case 1 :
					if(hNotepad == NULL)
						break;

					rcWndNotepad.left = rcWndNotepadInitial.left;
					rcWndNotepad.top = rcWndNotepadInitial.top;
					rcWndNotepadClient.right = rcWndNotepadClientInitial.right;
					rcWndNotepadClient.bottom = rcWndNotepadClientInitial.bottom;

					SendMessage(hNotepad, WM_SETICON, ICON_BIG, (LPARAM)hNotepadIcon);
					SetMenu(hNotepad, hMenu);
					DrawMenuBar(hNotepad);
					SetWindowText(hNotepad, szNotepadWindowName);
					// SendMessage(hNotepad, WM_SETTEXT, 0, (LPARAM)szNotepadWindowName);
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					EnumChildWindows(hNotepad, EnumChildProc, 0);
					break;

				// Button - Move Npotepad Left
				case 2 :
					rcWndNotepad.left = rcWndNotepad.left - 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad. top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Remove Menu
				case 3 :
					SetMenu(hNotepad, NULL);
					break;

				// Button - Change Window Name
				case 4 :
					SetWindowText(hNotepad, TEXT("Kalyani Dhapodkar"));
					break;

				// Button - Change Icon
				case 5 :
					SendMessage(hNotepad, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
					break;

				// Button - Move Notepad Up
				case 6 :
					rcWndNotepad.top = rcWndNotepad.top - 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Move Window(5, 5, 500, 300)
				case 7 :
					rcWndNotepad.left = 5;
					rcWndNotepad.top = 5;
					rcWndNotepadClient.right = 500;
					rcWndNotepadClient.bottom = 300;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Move Notepad Down
				case 8 :
					rcWndNotepad.top = rcWndNotepad.top + 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad. top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Add Text With Change Font
				case 9 :
					if(hNotepad == NULL)
						break;
					
					EnumChildWindows(hNotepad, EnumChildProc, 1);
					break;

				// Button - Increase Horizontal Size
				case 10 :
					rcWndNotepadClient.right = rcWndNotepadClient.right + 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Increase Vertical Size
				case 11 :
					rcWndNotepadClient.bottom = rcWndNotepadClient.bottom + 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Move Notepad Right
				case 12 :
					rcWndNotepad.left = rcWndNotepad.left + 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Decrease Horizontal Size
				case 13:
					rcWndNotepadClient.right = rcWndNotepadClient.right - 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Decrease Vertical Size
				case 14:
					rcWndNotepadClient.bottom = rcWndNotepadClient.bottom - 50;
					MoveWindow(hNotepad, rcWndNotepad.left, rcWndNotepad.top, rcWndNotepadClient.right, rcWndNotepadClient.bottom, TRUE);
					break;

				// Button - Close Notepad
				case 15:
					PostMessage(hNotepad, WM_DESTROY, 0, 0);
					hNotepad = NULL;
					break;

				// Default for no match
				default:
					break;
			}
			break;

		// Append the menu in Application's System Menu
		case WM_SYSCOMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_SYS_ABOUT:
					MessageBox(hwnd, TEXT("This Application is Created by\n Kalyani Dhapodkar\n")
										TEXT("Under the guidance of\nDr. Vijay Gokhale Sir\n"), 
										szAppName2, MB_OK | MB_ICONINFORMATION);
					break;
			}
			break;

		// Destroys the Parent Window 
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

/*
	Function Name - EnumWindowsProc
	Description  -	* A Callback Function which enumerates all the top level windows
					* Gets the Window's Name of all top level windows one by one
					* Compares them with the window name we want
						and stores the handle of that window
	INPUT PARAMETER - 	1. hwnd - handle of the window ( enumrating window)
						2. lParam - contains additional long data/information
	RETURN -  TRUE - If handle found
			  FALSE - If handle NOT found
*/	

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	// Local Variable Declaration
	TCHAR hwndWindowName[255] = TEXT("");

	// Code
	// Get Window Text at even iteration 
	GetWindowText(hwnd, hwndWindowName, 100);

	// Compares Window Name with required Window Name
	if(CompareWindowsNames(hwndWindowName, szNotepadWindowName))
	{
		hNotepad = hwnd;
		return(FALSE);
	}

	return(TRUE);
}


/*
	Function Name - CompareWindowsNames
	Description  -	* First compares the length of two strings
					* Then compares the strings
	INPUT PARAMETER - 	1. strName1 - first string
						2. strName2 - Second String
	RETURN -  1 - If both are SAME
			  0 - If NOT SAME
*/	

BOOL CompareWindowsNames(TCHAR* strName1, TCHAR* strName2)
{
	// Local Variable Declaration
	int i;
	int lenStrName1 = 0, lenStrName2 = 0;

	// Code
	for(i = 0; strName1[i] != '\0'; i++)
		lenStrName1++;

	for(i = 0; strName2[i] != '\0'; i++)
		lenStrName2++;

	// Checking strings length are equal or not
	if(lenStrName1 != lenStrName2)
		return(0);

	if(lenStrName1 == lenStrName2)
	{
		for( i = 0; i != lenStrName1; i++)
		{
			if(strName1[i] == strName2[i] )
				continue;
			else
				return(1);
		}
	}

	return(1);
}


/*
	Function Name - EnumChildProc
	Description  -	* Create the Font with required specifications
					* Change Window font with Created Font style
					* Prints the Sentence with New Font Style
	INPUT PARAMETER - 	1. hwnd - Handle to a window
						2. LPARAM - extra information 
									- here 1/0 to tell whether str to be
										added to str to print or not
										1 - add
										0 - don't add
	RETURN -  1 - If both are SAME
			  0 - If NOT SAME
*/	

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
	// Local Variable Declaration
	TCHAR strenumchildproc[50] = TEXT("");
	HFONT hFont;
	
	// Code
	// creates and stores formatted font in hFont
	hFont = CreateFont(48, 0, 0, 0, 700, TRUE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_ROMAN, TEXT("Impact"));
	
	// Change Window Font with Created Font
	SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	if(lParam)
	{
		// Add string to str
		wsprintf(strenumchildproc, TEXT("Times New Roman has made as default Font"));
	}
	// Sets/Prints the newly fonted string
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)strenumchildproc);

	return(TRUE);
 }

