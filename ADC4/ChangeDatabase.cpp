#include "ADC4.h"
#include "globals.h"
#include "ACDS.h"
#include "DatabaseKey.h"
#include "DatabaseInformation.h"
#include "Menus.h"

void ChangeDatabaseMenu(void) {
	std::filesystem::path filepath;
	bool validInput = false;
	AuliaDBType newDB;
	bool exitMenu = false;
	while (!exitMenu) {
		conio::clrscr();
		std::cout << "Database Selector" << std::endl;
		std::cout << "\tCurrent Database: " << GetDatabaseName() << std::endl;
		std::cout << std::endl;
		std::cout << "\t1.  Items" << std::endl;
		std::cout << "\t2.  Enemies" << std::endl;
		std::cout << "\t0.  Unload Database" << std::endl;
		std::cout << "\tESC Return to main" << std::endl;
		switch (tolower(conio::getch())) {
		case '1':
			newDB = DB_ITEM;
			break;
		case '2':
			newDB = DB_ENEMY;
			break;
		case '0':
			newDB = DB_NONE;
			break;
		case '\033':
			return;
		default:
			conio::invalidInput();
			continue;
		}

		switch (newDB) {
		case DB_ITEM:
			filepath = std::filesystem::path(DatabaseLocation + "\\ITEM");
			break;
		case DB_ENEMY:
			filepath = std::filesystem::path(DatabaseLocation + "\\ENEMY");
			break;
		case DB_NONE:
			selectedDB = DB_NONE;
			DBStatus = 0;
			continue;
		default:
			return;
		}

		selectedDB = newDB;
		int status = CheckKey(filepath);
		if (status != 0) DBStatus = 1;
		if (status == -1) DBStatus = -1;
	}
	return;
}