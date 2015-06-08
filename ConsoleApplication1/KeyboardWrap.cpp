#include "KeyboardWrap.h"


KeyboardWrap::KeyboardWrap(void)
{
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
}

void KeyboardWrap::typeString (std::string inputs) {
	for (int i = 0; i < inputs.size(); i++) 
	{
		click(inputs.at(i));
	}
}

void KeyboardWrap::press(char input) {
	ip.ki.wVk = getKeyNumber(input); // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
}

void KeyboardWrap::release(char input) {
	Sleep(CLICK_INTERVAL);
	ip.ki.wVk = getKeyNumber(input);
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}

void KeyboardWrap::click (char input){
	press(input);
	release(input);
}

WORD KeyboardWrap::getKeyNumber(char inputChar) {
	return inputChar;
}

KeyboardWrap::~KeyboardWrap(void)
{
}
