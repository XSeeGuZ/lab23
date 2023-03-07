#include <windows.h>
#include <stdio.h>

/* This is where all the input to the window goes to */
HWND textfield,Plus,Ninus,Time,Divide;
char textSaved1[100],textSaved2[100];
HWND TextBox1,TextBox2;
char t[100];
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
		textfield = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE | WS_CHILD ,30,10,170,20,hwnd, NULL ,NULL ,NULL);
		TextBox1 = CreateWindow("EDIT","",WS_BORDER | WS_CHILD | WS_VISIBLE,20 ,40,190,30,hwnd, NULL,NULL,NULL);
		TextBox2 = CreateWindow("EDIT","",WS_BORDER | WS_CHILD | WS_VISIBLE,20 ,70,190,30,hwnd, NULL,NULL,NULL);
		Plus = CreateWindow ("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER,20,110,40,30,hwnd, (HMENU) 1,NULL,NULL);
		Ninus = CreateWindow ("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER,70,110,40,30,hwnd, (HMENU) 2,NULL,NULL);
		Time = CreateWindow ("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER,120,110,40,30,hwnd, (HMENU) 3,NULL,NULL);
		Divide = CreateWindow ("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER,170,110,40,30,hwnd, (HMENU) 4,NULL,NULL);
		
		//CreateWindow("BUTTON","Go",WS_VISIBLE | WS_CHILD | WS_BORDER,420,10,70,20,hwnd, (HMENU) 2, NULL,NULL);
		break;

		case WM_COMMAND:{
			
			switch (LOWORD(wParam))
			{
				case 1:
					float num1p,num2p,totalp;
					GetWindowText(TextBox1,&textSaved1[0],100);
					GetWindowText(TextBox2,&textSaved2[0],100);
					num1p = atof(textSaved1);
					num2p = atof(textSaved2);
					totalp = num1p+num2p;
					sprintf(t, "%f", totalp);
					::MessageBox(hwnd,t,"Result",MB_OK);
				break;
				case 2:
					float num1n,num2n,totaln;
					GetWindowText(TextBox1,&textSaved1[0],100);
					GetWindowText(TextBox2,&textSaved2[0],100);
					num1n = atof(textSaved1);
					num2n = atof(textSaved2);
					totaln = num1n-num2n;
					sprintf(t, "%f", totaln);
					::MessageBox(hwnd,t,"Result",MB_OK);
				break;
				case 3:
					float num1t,num2t,totalt;
					GetWindowText(TextBox1,&textSaved1[0],100);
					GetWindowText(TextBox2,&textSaved2[0],100);
					num1t = atof(textSaved1);
					num2t = atof(textSaved2);
					totalt = num1t*num2t;
					sprintf(t, "%f", totalt);
					::MessageBox(hwnd,t,"Result",MB_OK);
				break;
				case 4:
					float num1d,num2d,totald;
					GetWindowText(TextBox1,&textSaved1[0],100);
					GetWindowText(TextBox2,&textSaved2[0],100);
					num1d = atof(textSaved1);
					num2d = atof(textSaved2);
					totald = num1d/num2d;
					sprintf(t, "%f", totald);
					::MessageBox(hwnd,t,"Result",MB_OK);
				break;
			}


			break;
		}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}


			
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+5);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}