#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include <string>

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

BOOL CALLBACK enumDesktopWindowsProc(__in HWND hWnd, __in  LPARAM lParam) {
    
	TCHAR* buffer = printWindowText(hWnd);
	if (buffer == NULL) return TRUE;

    wstring s2 ( buffer );
    wstring s3 (L"Ning") ;
    std::string::size_type found = s2.find(s3);
    if (found!=std::string::npos)
    {
      // SendMessage(hWnd,WM_DESTROY,0,0);
		HWND child = ::GetWindow(hWnd, GW_CHILD);
		cout << "Child : ";

		printWindowText(hWnd);
    }
    delete[] buffer;
    return TRUE;
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

	//	cout << "Is visibal: ";
		 if (!IsWindowVisible(hWnd)) {
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			EnableWindow(hWnd, TRUE);
			SetForegroundWindow(hWnd);

			Sleep(100);

			INPUT ip;
			ip.type = INPUT_KEYBOARD;
			ip.ki.wScan = 0; // hardware scan code for key
			ip.ki.time = 0;
			ip.ki.dwExtraInfo = 0;
 
			// Press the "A" key
			ip.ki.wVk = 0x41; // virtual-key code for the "a" key
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));
			// Release the "A" key
		    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
		    SendInput(1, &ip, sizeof(INPUT));

			// cout << "input a" << endl;
			
			INPUT ip2;
			ip2.type = INPUT_KEYBOARD;
			ip2.ki.wVk = 0x0D; // virtual-key code for the "Enter" key
			ip2.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip2, sizeof(INPUT));
			// Release the "Enter" key
			ip2.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip2, sizeof(INPUT));
			
			Sleep(1000);
		 	SendMessage(hWnd, WM_CLOSE, 0, 0);
		 }
    }
    delete[] buffer;
    return TRUE;
}

BOOL CALLBACK enumWindowStations(_In_ LPTSTR lpszWindowStation, __in  LPARAM lParam) {
	std::cout << "Hellow world2" << endl;
    std::cout << (lpszWindowStation) <<endl;
    return TRUE;
}

int main(int argc, char* argv[])
{
	std::cout << "Hellow world" << endl;

	// Get current thread
	// DWORD dwThreadId = GetCurrentThreadId();
	while (true) { 
		BOOL enumeratingWindowsSucceeded2 = ::EnumWindows(enumWindowsProc, NULL);
		Sleep(3000);
	}
	return 0;
}