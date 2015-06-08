#pragma once
#include <Windows.h>
#include <cstring>
#include <string>

class KeyboardWrap
{
public:
	KeyboardWrap(void);
	~KeyboardWrap(void);

	void press(char input);
	void release(char input);
	void click(char input);

	void typeString (std::string inputs);

	const static int CLICK_INTERVAL = 100;

private:
	INPUT ip;
	WORD getKeyNumber(char inputChar) ;
};

