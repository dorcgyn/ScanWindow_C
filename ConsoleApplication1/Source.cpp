#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include <string>

using namespace std;

BOOL CALLBACK enumDesktopWindowsProc(__in HWND hWnd, __in  LPARAM lParam) {
	int length = ::GetWindowTextLength(hWnd);
	if (0==length) return true;

	TCHAR* buffer;
	buffer = new TCHAR[length+1];
	memset( buffer, 0, (length+1)*sizeof(TCHAR));
	
	GetWindowText( hWnd, buffer, length + 1 );
    wcout <<buffer<<endl;
    wstring s2 ( buffer );
    wstring s3 (L"Ning") ;
    std::string::size_type found = s2.find(s3);
    if (found!=std::string::npos)
    {
      // SendMessage(hWnd,WM_DESTROY,0,0);
		HWND child = ::GetWindow(hWnd, GW_CHILD);
		cout << "Child : ";

		length = ::GetWindowTextLength(child);
		if (0!=length) {
		TCHAR* buffer2;
		buffer2 = new TCHAR[length+1];
		memset( buffer2, 0, (length+1)*sizeof(TCHAR));
	
		GetWindowText( child, buffer2, length + 1 );
		wcout <<buffer2<<endl;
		}
    }
    delete[] buffer;
    return TRUE;
}

BOOL CALLBACK enumWindowsProc(__in HWND hWnd, __in  LPARAM lParam) {
	int length = ::GetWindowTextLength(hWnd);
	if (0==length) return true;

	TCHAR* buffer;
	buffer = new TCHAR[length+1];
	memset( buffer, 0, (length+1)*sizeof(TCHAR));
	
	GetWindowText( hWnd, buffer, length + 1 );
    wcout <<buffer<<endl;
    wstring s2 ( buffer );
    wstring s3 (L"Ning") ;
    std::string::size_type found = s2.find(s3);
    if (found!=std::string::npos)
    {
      // SendMessage(hWnd,WM_DESTROY,0,0);
		HWND child = ::GetWindow(hWnd, GW_CHILD);
		cout << "Child : ";

		length = ::GetWindowTextLength(child);
		if (0!=length) {
		TCHAR* buffer2;
		buffer2 = new TCHAR[length+1];
		memset( buffer2, 0, (length+1)*sizeof(TCHAR));
	
		GetWindowText( child, buffer2, length + 1 );
		wcout <<buffer2<<endl;
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
	DWORD dwThreadId = GetCurrentThreadId();
	HDESK hDesktop = GetThreadDesktop(dwThreadId);
	BOOL enumeratingWindowsSucceeded = ::EnumDesktopWindows(hDesktop, enumDesktopWindowsProc, NULL);
	std::cout << "Hellow world 3" << endl;
	BOOL enumeratingWindowsSucceeded2 = ::EnumWindows(enumWindowsProc, NULL);
	return 0;
}