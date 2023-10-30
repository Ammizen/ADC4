#include "conio.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
namespace conio {
	namespace {
		void initTerminal(bool echo) {
			GetConsoleMode(hConsole, &old);
			current = old;
			if (echo) current |= ENABLE_ECHO_INPUT;
			else current &= ~ENABLE_ECHO_INPUT;
			SetConsoleMode(hConsole, current);
		}
		void resetTerminal(void) {
			SetConsoleMode(hConsole, old);
		}
		//char getch_(bool echo) {
		//	char ch;
		//	initTerminal(echo);
		//	ch = getchar();
		//	resetTerminal();
		//	return ch;
		//}
		bool checkIfNumber(char c) {
			if ((c - char("0") < 0) || (c - char("0") > 9)) return true;
			return false;
		}
	}
	char getch(void) {
		std::cout << std::flush;
		return _getch();
	}
	char getche(void) {
		std::cout << std::flush;
		return _getche();
	}
	void pause(void) {
		printf("\nPress any key to continue...");
		getch();
	}
	void setCursorPos(int x, int y) {
		printf("\033[" + x + ';' + y + 'H');
	}

	void disableConsoleCursor(void) {
		printf("\033?25l");
	}

	void invalidInput(void) {
		printf("\n\tInvalid Input");
		pause();
	}

	void clrscr(void) {
		printf("\033[2J\033[H\033[3J");
	}

	bool consolePromptBool(void) {
		printf(" (y/n)");
		char input = '0';
		while ((input != 'y') && (input != 'n')) {
			input = tolower(getch());
		}
		if (input == 'y') return true;
		return false;
	}

	int consolePromptInt(int digits = -1, bool specialCharactersEnabled = true) {
		printf(" (0-9)");
		std::string acc = "";
		char input;
		char* pEnd;
		bool valid = false;
		while ((acc.size() < digits) || (digits < 1)) {
			while (!valid) {
				input = getch();
				if ((input - char("0") < 0) || (input - char("0") > 9)) { valid = true; break; }
				if (input == '\b' || input == '\127') { acc.resize(acc.size() - 1); }
				if (specialCharactersEnabled) {
					if (input == '\033') { return -1; } //Escape returns -1
					if (input == '\n') { return std::strtol(acc.c_str(), &pEnd, 10); } //Enter returns early
				}
				printf("\a\r\033[K\r");
				printf(acc.c_str());
			}
			acc += input;
			printf("\r\033[K\r");
			printf(acc.c_str());
		}
		return std::strtol(acc.c_str(), &pEnd, 10);
	}
}
#endif
#ifdef unix
#include <termios.h>
namespace conio {
	namespace {
		void initTerminal(bool echo) {
			tcgetattr(0, &old);
			current = old;
			current.c_lflag &= ~ICANON; //Disable buffered i/o
			if (echo) current.c_lflag |= ECHO; //Set echo mode
			else current.c_lflag &= ~ECHO; //Set no echo mode
			tcsetattr(0, TCSANOW, &current); //Push new terminal settings
		}

		void resetTerminal(void) {
			tcsetattr(0, TCSANOW, &old);
		}

		char getch_(bool echo) {
			std::cout << std::flush;
			char ch;
			initTerminal(echo);
			ch = getchar();
			resetTerminal();
			return ch;
		}

		bool checkIfNumber(char c) {
			if ((c - char('0') < 0) || (c - char('0') > 9)) return true;
			return false;
		}
	}

	char getch(void) {
		return getch_(false);
	}

	char getche(void) {
		return getch_(true);
	}

	void pause(void) {
		printf("\n\tPress any key to continue...\n");
		getch();
	}

	void setCursorPos(int x, int y) {
		printf("\033[" + x + ';' + y + 'H');
	}

	void disableConsoleCursor(void) {
		printf("\033?25l");
	}

	void invalidInput(void) {
		printf("\n\tInvalid Input");
		pause();
	}

	void clrscr(void) {
		printf("\x1B[2J\x1B[H");
	}

	bool consolePromptBool(void) {
		printf(" (y/n)");
		char input = '0';
		while ((input != 'y') && (input != 'n')) {
			input = tolower(getch());
		}
		if (input == 'y') return true;
		return false;
	}

	int consolePromptInt(int digits = -1, bool specialCharactersEnabled = true) {
		printf(" (0-9)");
		std::string acc = "";
		char input;
		char* pEnd;
		bool valid = false;
		while ((acc.size() < digits) || (digits < 1)) {
			while (!valid) {
				input = getch();
				if ((input - char('0') < 0) || (input - char('0') > 9)) { valid = true; break; }
				if (input == '\b' || input == '\127') { acc.resize(acc.size() - 1); }
				if (specialCharactersEnabled) {
					if (input == '\033') { return -1; } //Escape returns -1
					if (input == '\n') { return std::strtol(acc.c_str(), &pEnd, 10); } //Enter returns early
				}
				printf("\a\r\033[K\r");
				printf(acc.c_str());
			}
			acc += input;
			printf("\r\033[K\r");
			printf(acc.c_str());
		}
		return std::strtol(acc.c_str(), &pEnd, 10);
	}
}
#endif