#include "ADC4.h"
#include "globals.h"
#include "ACDS.h"
#include "DatabaseKey.h"
#include "DatabaseInformation.h"
#include "CustomStringUtils.h"
#include "Menus.h"

void LoadKeys() {
	std::fstream keyIn(DatabaseLocation + DIRSEP + GetDatabaseName() + DIRSEP +"key.csv");
	if (keyIn.fail()) return;
	char* str = new char[1000000]; //1MB
	std::vector<std::string> Key[11];
	for (int i = 0; i < 11; i++) {
		keyIn.getline(str, 1000000);
		Key[i] = SplitString(str, ",");
	}
	delete[] str;
	sysdat.elementList = Key[0];
	sysdat.skilltypeList = Key[1];
	sysdat.weapontypeList = Key[2];
	sysdat.armortypeList = Key[3];
	sysdat.equipmenttypeList = Key[4];
	sysdat.itemTypeList = Key[5];
	sysdat.itemEffectTypeList = Key[6];
	sysdat.statusEffectList = Key[7];
	sysdat.magicAbilityTypes = Key[8];
	sysdat.physAbilityTypes = Key[9];
	sysdat.passiveAbilityTypes = Key[10];
	return;
}

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
			filepath = std::filesystem::path(DatabaseLocation + DIRSEP + "ITEM");
			break;
		case DB_ENEMY:
			filepath = std::filesystem::path(DatabaseLocation + DIRSEP + "ENEMY");
			break;
		case DB_NONE:
			selectedDB = DB_NONE;
			DBStatus = 0;
			continue;
		default:
			return;
		}

		selectedDB = newDB;
		LoadKeys();
		int status = CheckKey(filepath);
		if (status != 0) DBStatus = 1;
		if (status == -1) DBStatus = -1;
	}
	return;
}