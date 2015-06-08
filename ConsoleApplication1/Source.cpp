#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include <string>
#include "KeyboardWrap.h"

using namespace std;

int i = 0;

TCHAR* printWindowText (HWND hWnd) {
	int length = ::GetWindowTextLength(hWnd);
	if (0==length) return NULL;
	
	TCHAR* buffer = new TCHAR[length+1];
	memset( buffer, 0, (length+1)*sizeof(TCHAR));
	
	GetWindowText( hWnd, buffer, length + 1 );
    // wcout << buffer << endl;
	return buffer;
}


BOOL CALLBACK enumWindowsProc(__in HWND hWnd, __in  LPARAM lParam) {
	i++;
	TCHAR* buffer = printWindowText(hWnd);
	if (buffer == NULL) return TRUE;

    wstring s2 ( buffer );
    // wstring s3 (L"Yu (HP") ;
	wstring s3 (L"Tan, Chris") ;
    std::string::size_type found = s2.find(s3);
	
    if (found!=std::string::npos)
    {
      // SendMessage(hWnd,WM_DESTROY,0,0);
		HWND ancestor = ::GetAncestor(hWnd, GA_ROOTOWNER);

		// cout << "Ancentor: ";
		printWindowText(ancestor);

		// cout << "Window INof:  " << endl;
		WINDOWINFO winInfo;
		GetWindowInfo(hWnd, &winInfo);
		// cout << winInfo.rcWindow.left << "; top " << winInfo.rcWindow.top << "; right " << winInfo.rcWindow.right << "; bottom " << winInfo.rcWindow.bottom << endl;

		RECT rect;
		GetWindowRect(hWnd, &rect);
//		cout << rect.left << "; top " << rect.top << "; right " << rect.right << "; bottom " << rect.bottom << endl;

		 if (!IsWindowVisible(hWnd)) {
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			EnableWindow(hWnd, TRUE);
			SetForegroundWindow(hWnd);

			Sleep(100);

			KeyboardWrap key;
			key.typeString("Auto reply, I am not here~~");
			
			Sleep(1000);
		 	SendMessage(hWnd, WM_CLOSE, 0, 0);
		 }
    }
    delete[] buffer;
    return TRUE;
}


int main(int argc, char* argv[])
{
	std::cout << "Hellow world" << endl;

	while (true) { 
		BOOL enumeratingWindowsSucceeded2 = ::EnumWindows(enumWindowsProc, NULL);
		Sleep(3000);
	}
	return 0;
}