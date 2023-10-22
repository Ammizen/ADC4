#pragma once
#include <stdio.h>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
namespace conio {
	namespace {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		static DWORD old, current;
		void initTerminal(bool echo);
		void resetTerminal(void);
		char getch_(bool echo);
		bool checkIfNumber(char c);
	}
	char getch(void);
	char getche(void);
	void pause(void);
	void setCursorPos(int x, int y);
	void disableConsoleCursor(void);
	void invalidInput(void);
	void clrscr(void);
	bool consolePromptBool(void);
	int consolePromptInt(int digits, bool specialCharactersEnabled);
}
#endif
#ifdef unix
#include <termios.h>
namespace conio {
	namespace {
		static struct termios old, current;
		void initTerminal(bool echo);
		void resetTerminal(void);
		char getch_(bool echo);
		bool checkIfNumber(char c);
	}

	char getch(void);
	char getche(void);
	void pause(void);
	void setCursorPos(int x, int y);
	void disableConsoleCursor(void);
	void invalidInput(void);
	void clrscr(void);
	bool consolePromptBool(void);
	int consolePromptInt(int digits = -1, bool specialCharactersEnabled = true);
}
#endif