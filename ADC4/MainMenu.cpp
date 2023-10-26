#include "ADC4.h"
#include "DatabaseInformation.h"
#include "Menus.h"
#include "CreateEntry.h"
#include "SaveData.h"
#include "ExportData.h"

void MainMenu(void) {
	bool exitMenu = false;
	std::string controlChar = "";
	std::string controlEnd = "\033[m";
	while (!exitMenu) {
		conio::clrscr();
		std::cout << "Current Database: " << GetDatabaseName() << std::endl;

		switch (DBStatus) {
		case -1:
			std::cout << "WARNING: Keyfile was missing from database.\n\tSome data may be unusable." << std::endl;
			break;

		case 1:
			std::cout << "CAUTION: Keyfile appears to be out of date.\n\tRecommend: Run database update utility." << std::endl;
			break;
		}

		std::cout << std::endl;

		std::cout << "Main Menu:" << std::endl;
		std::cout << std::endl;

		controlChar = (selectedDB == DB_NONE) ? "\033[31;100m" : "";

		std::cout << controlChar << "\t1.  Create Entry     " << std::endl
			<< "\t2.  Open Entry       " << std::endl
			<< "\t3.  Edit Active Entry" << std::endl
			<< "\t4.  Write Entry      " << std::endl
			<< "\t5.  Export Menu      " << std::endl
			<< "\t6.  Compiler Menu    " << std::endl
			<< "\t7.  Update Database  " << std::endl
			<< "\t8.  Edit Database Key" << controlEnd << std::endl
			<< "\t0.  Change Database  " << std::endl
			<< "\t~   System Options   " << std::endl
			<< "\tESC Exit Program     " << std::endl;

		char sel = tolower(conio::getch());

		switch (sel) {
		case '1':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			CreateEntry();
			break;
		case '2':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			OpenEntryMenu();
			break;
		case '3':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			EditEntryMenu();
			break;
		case '4':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			SaveData();
			break;
		case '5':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			ExportData();
			break;
		case '6':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			break;
		case '7':
			if (selectedDB == DB_NONE) { std::cout << "\a"; break; }
			break;
		case '8':
			break;
		case '0':
			ChangeDatabaseMenu();
			break;
		case '~':
		case '`':
			EditSettings();
			break;
		case '\033':
			ExitProgram(false);
			break;
		default:
			conio::invalidInput();
			break;
		}
	}
}