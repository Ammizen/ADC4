#include "UpdateDatabaseKey.h"
#include "DatabaseInformation.h"
#include "ParseData.h"
#include "SerializeData.h"
#include "CustomStringUtils.h"

void UpdateEntry(std::vector<bool>* entry, std::vector<std::string> oldKey[], int keyID) {
	oldKey += keyID;
	std::vector<std::string>* newKey;
	switch (keyID) {
	case 0:
		newKey = &sysdat.elementList;
		break;
	case 1:
		newKey = &sysdat.skilltypeList;
		break;
	case 2:
		newKey = &sysdat.weapontypeList;
		break;
	case 3:
		newKey = &sysdat.armortypeList;
		break;
	case 4:
		newKey = &sysdat.equipmenttypeList;
		break;
	case 5:
		newKey = &sysdat.itemTypeList;
		break;
	case 6:
		newKey = &sysdat.itemEffectTypeList;
		break;
	case 7:
		newKey = &sysdat.statusEffectList;
		break;
	case 8:
		newKey = &sysdat.magicAbilityTypes;
		break;
	case 9:
		newKey = &sysdat.physAbilityTypes;
		break;
	case 10:
		newKey = &sysdat.passiveAbilityTypes;
		break;
	}
	std::vector<bool> tmp(newKey->size());
	int emplacePtr = 0;
	for (std::string ns : *newKey) {
		int pullPtr = 0;
		for (std::string os : *oldKey) {
			if (ns == os) { tmp[emplacePtr] = entry->at(pullPtr); break; }
			pullPtr++;
		}
		emplacePtr++;
	}
}

template<>
void UpdateEntry<Item>(std::vector<unsigned char>* data, std::vector<std::string>* oldKey) {
	Item item = ParseData<Item>(data);
	UpdateEntry(&item.data.itemType, oldKey, 5);
	std::list<ItemEffect>::iterator itr = item.effects.begin();
	for (ItemEffect ie : item.effects) {
		UpdateEntry(&ie.ElementFlags, oldKey, 0);
		UpdateEntry(&ie.AfflictionFlags, oldKey, 7);
		*itr = ie;
	}
	*data = SerializeData<Item>(&item);
}

template<>
void UpdateEntry<Enemy>(std::vector<unsigned char>* data, std::vector<std::string>* oldKey) {
	Enemy enemy = ParseData<Enemy>(data);
	return;
}

void UpdateDatabaseKeyMenu(void) {
	conio::clrscr();
	std::cout << "Update the current database's keys?\n\tCaution: This may take a while." << std::endl;
	if (!conio::consolePromptBool()) return;

	std::cout << "Loading old key..." << std::endl;
	std::fstream keyIn(DatabaseLocation + "\\" + GetDatabaseName() + "\\key.csv");
	char* str = new char[1000000]; //1MB
	std::vector<std::string> Key[11];
	for (int i = 0; i < 11; i++) {
		keyIn.getline(str, 1000000);
		Key[i] = SplitString(str, ",");
	}
	delete[] str;
	std::cout << "Updating entries..." << std::endl;
	for (auto& entry : fs::directory_iterator(DatabaseLocation + "/" + GetDatabaseName())) {
		std::vector<unsigned char> data(entry.file_size());
		int counter = 0;
		std::fstream fin(entry.path().string(), std::ios::in | std::ios::binary);
		while (!fin.eof()) { data[counter] = fin.get(); counter++; }
		fin.close();
		switch (selectedDB) {
		case DB_ITEM:
			UpdateEntry<Item>(&data, Key);
			break;
		case DB_ENEMY:
		default:
			return;
		}
		remove(entry.path());
		std::fstream fout(entry.path().string(), std::ios::out | std::ios::binary);
		for (unsigned char c : data) {
			fout << c;
		}
		fout << std::flush;
		fout.close();
	}
}