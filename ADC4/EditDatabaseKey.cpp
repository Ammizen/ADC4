#include "EditDatabaseKey.h"

void AddEntry(std::vector<std::string>* key) {
	conio::clrscr();
	std::cout << "Please enter the new key's name:\n\t" << std::flush;
	char tmp[255];
	std::cin.getline(tmp, 255);
	std::cin.clear();
	key->push_back(tmp);
	return;
}

void DelEntry(std::vector<std::string>* key) {
	int ID;
	std::cout << "\033[2K\rPlease type the ID you wish to remove, followed by enter:\n\t\t" << std::flush;
	std::cin >> ID;

	if ((ID < 0) || (ID >= key->size())) { conio::invalidInput(); return; }

	key->erase(key->begin() + ID);
	std::cout << "\t\tSuccessfully deleted entry!";
	conio::pause();
	return;
}

void MoveMoveEntry(std::vector<std::string>* key) {
	int IDa, IDb;
	std::cout << "\033[2K\rPlease enter the ID that you wish to move: ";
	std::cin >> IDa;
	if ((IDa < 0) || (IDa >= key->size())) { conio::invalidInput(); return; }
	std::cout << "\033[2K\rPlease enter the target index for the entry: ";
	std::cin >> IDb;
	if ((IDb < 0) || (IDb >= key->size())) { conio::invalidInput(); return; }
	move(*key, IDa, IDb);
	std::cout << "\033[2K\rSuccessful move!";
	conio::pause();
	return;
}

void MoveSwapEntry(std::vector<std::string>* key) {
	int IDa, IDb;
	std::cout << "\033[2K\rPlease enter the ID that you wish to move: ";
	std::cin >> IDa;
	if ((IDa < 0) || (IDa >= key->size())) { conio::invalidInput(); return; }
	std::cout << "\033[2K\rPlease enter the target index for the entry: ";
	std::cin >> IDb;
	if ((IDb < 0) || (IDb >= key->size())) { conio::invalidInput(); return; }
	std::swap(key->at(IDa), key->at(IDb));
	std::cout << "\033[2K\rSuccessful swap!";
	conio::pause();
	return;
}

void MoveEntry(std::vector<std::string>* key) {
	int IDa, IDb;
	std::cout << "\033[2K\rS: Swap Entries / M: Move Entries" << std::flush;
	switch (std::tolower(conio::getch())) {
	case 's':
		MoveSwapEntry(key);
		break;
	case 'm':
		MoveMoveEntry(key);
		break;
	default:
		conio::invalidInput();
		return;
	}
}

void EditKey(std::vector<std::string>* key, std::string keyname) {
	char sel;
	int counter = 0;
	bool ExitMenu = false;
	while (!ExitMenu) {
		conio::clrscr();
		std::cout << "Editing key: " << keyname << std::endl;
		for (std::string s : *key) {
			std::cout << "\t" << counter << "." << s << std::endl;
			counter++;
		}
		std::cout << "A: Add Entry / D: Delete Entry / M: Move Entry / ESC: Back\033[n";

		sel = std::tolower(conio::getch());
		switch (sel) {
		case 'a':
			AddEntry(key);
			break;
		case 'd':
			DelEntry(key);
			break;
		case 'm':
			MoveEntry(key);
			break;
		case '\033':
			return;
		default:
			conio::invalidInput();
			break;
		}
		counter = 0;
	}
}

void EditDBKeyMenu(void) {
	char sel;
	bool ExitMenu = false;
	while (!ExitMenu) {
		conio::clrscr();
		std::cout << "Select a key to edit.\n\t\033[91mCaution: Editing a key incorrectly may result in errors.\033[m\n" << std::endl;

		std::cout << "\t1. Element List" << std::endl
			<< "\t2. Skill Types List" << std::endl
			<< "\t3. Weapon Types List" << std::endl
			<< "\t4. Armor Types List" << std::endl
			<< "\t5. Equipment Type List" << std::endl
			<< "\t6. Item Type List" << std::endl
			<< "\t7. Item Effect List" << std::endl
			<< "\t8. Status Effect List" << std::endl
			<< "\t9. Magic Ability Types" << std::endl
			<< "\tA. Physical Ability Types" << std::endl
			<< "\tB. Passive Ability Types" << std::endl
			<< "\tESC - Return" << std::endl;

		sel = std::tolower(conio::getch());
		switch (sel) {
		case '1':
			EditKey(&sysdat.elementList, "Elements");
				break;
		case '2':
			EditKey(&sysdat.skilltypeList, "Skill Types");
			break;
		case '3':
			EditKey(&sysdat.weapontypeList, "Weapon Types");
			break;
		case '4':
			EditKey(&sysdat.armortypeList, "Armor Types");
			break;
		case '5':
			EditKey(&sysdat.equipmenttypeList, "Equipment Types");
			break;
		case '6':
			EditKey(&sysdat.itemTypeList, "Item Types");
			break;
		case '7':
			EditKey(&sysdat.itemEffectTypeList, "Item Effect Types");
			break;
		case '8':
			EditKey(&sysdat.statusEffectList, "Status Effects");
			break;
		case '9':
			EditKey(&sysdat.magicAbilityTypes, "Magic Types");
			break;
		case 'a':
			EditKey(&sysdat.physAbilityTypes, "Physical Ability Types");
			break;
		case 'b':
			EditKey(&sysdat.passiveAbilityTypes, "Passive Ability Types");
			break;
		case '\033':
			return;
		default:
			conio::invalidInput();
			break;
		}
	}
}