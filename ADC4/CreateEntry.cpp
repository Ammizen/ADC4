#include "ADC4.h"
#include "SaveData.h"
#include "Menus.h"

void CreateEntry() {
	conio::clrscr();
	if (UnsavedChanges) {
		std::cout << "Caution! You have changes in the buffer that have not yet been written!" << std::endl;
		std::cout << "\tWrite changes?" << std::flush;
		if (conio::consolePromptBool()) SaveData();
	}
	switch (selectedDB) {
	case DB_ITEM:
		activeEntry = Item();
		break;
	case DB_ENEMY:
		activeEntry = Enemy();
		break;
	}

	std::cout << "Successfully created new entry!" << std::endl;
	std::cout << "\tOpen editor now?";
	if (conio::consolePromptBool()) EditEntryMenu();
	return;
}