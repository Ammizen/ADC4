#include "OpenEntry.h"
#include "DatabaseInformation.h"



void OpenEntryMenu(void) {
	bool ExitMenu = false;
	while (!ExitMenu) {
		conio::clrscr();
		std::cout << "Selected database: " << GetDatabaseName() << std::endl;
		std::cout << "\t 1. Import Entry " << std::endl;
		std::cout << "\t 2. Load Entry   " << std::endl;
		std::cout << "\tESC Close menu   " << std::endl;

		int sel = conio::consolePromptInt(1, true);

		switch (sel) {
		case 1:
			// Import Entry Menu
			break;
		case 2:
			// Load Entry Menu
			break;
		case -1:
			ExitMenu = true;
			break;
		default:
			conio::invalidInput();
			break;
		}
	}

	//Exit Menu
	return;
}