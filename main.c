#include <stdio.h>
#include <windows.h>
#include <winuser.h>

#include "Draw.h"

// the keyboard hook that looks for function key presses.
HHOOK kbdHook;

// define the keyboard callback.
LRESULT WINAPI KbdHookProc(int,WPARAM,LPARAM);

void ReleaseHook()
{
	UnhookWindowsHookEx(kbdHook);
}


void SafeExit(){
	ReleaseHook();
	printf("Keyboard hook released.");
	

}

// impl of the keyboard callback.
LRESULT WINAPI KbdHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	switch(wParam){
		case 0x4A:
			printf("J pressed\n");
			break;
		case 0x51:
			SafeExit();
			exit(0);
			break;
	}

	return CallNextHookEx(kbdHook,nCode,wParam,lParam);
}

void SetHook()
{
	printf("Setting the hook...\n");
	// Set the keyboard hook. 
	kbdHook = SetWindowsHookEx
	(
		WH_KEYBOARD,
		KbdHookProc,
		NULL,
		0
	);

	if(kbdHook == NULL)
	{
		printf("Error; couldn't set the hook.\n");
		exit(1);
	}


}




int main()
{
	printf("Enabling ruler.\n");

	SetHook();

	MSG message;

	while (GetMessage(&message,NULL,0,0)){
		TranslateMessage(&message);
		DispatchMessage(&message);
	}


	SafeExit();

	printf("Main complete. Exiting...\n");
	return 0;
}