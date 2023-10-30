#include "UpdateDatabaseKey.h"
#include "DatabaseInformation.h"
#include "ParseData.h"
#include "SerializeData.h"
#include "CustomStringUtils.h"
#include "adcread.h"

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
void UpdateEntry<Item>(std::vector<unsigned char>* data, std::vector<std::string>* oldKey, std::string filename) {
	Item item = ParseData<Item>(data, filename);
	UpdateEntry(&item.data.itemType, oldKey, 5);
	std::list<ItemEffect>::iterator itr = item.effects.begin();
	for (ItemEffect ie : item.effects) {
		UpdateEntry(&ie.ElementFlags, oldKey, 0);
		UpdateEntry(&ie.AfflictionFlags, oldKey, 7);
		*itr = ie;
	}
	std::vector<unsigned char> tmp = SerializeData<Item>(&item);
	data->swap(tmp);
}

template<>
void UpdateEntry<Enemy>(std::vector<unsigned char>* data, std::vector<std::string>* oldKey, std::string filename) {
	Enemy enemy = ParseData<Enemy>(data);
	return;
}


void CreateNewKey() {
	std::vector<std::string> Key[11];
	std::fstream fout(DatabaseLocation + DIRSEP + GetDatabaseName() + DIRSEP + "key.csv", std::ios::out);
	
	Key[0] = sysdat.elementList;
	Key[1] = sysdat.skilltypeList;
	Key[2] = sysdat.weapontypeList;
	Key[3] = sysdat.armortypeList;
	Key[4] = sysdat.equipmenttypeList;
	Key[5] = sysdat.itemTypeList;
	Key[6] = sysdat.itemEffectTypeList;
	Key[7] = sysdat.statusEffectList;
	Key[8] = sysdat.magicAbilityTypes;
	Key[9] = sysdat.physAbilityTypes;
	Key[10] = sysdat.passiveAbilityTypes;
	for (std::vector<std::string> vs : Key) {
		std::stringstream ss;
		for (std::string s : vs) {
			ss << s << ",";
		}
		fout << ss.str().substr(0, ss.str().size()-1) << "\n";
	}
	fout << std::flush;
	fout.close();
	DBStatus = 0;
}

void UpdateDatabaseKeyMenu(void) {
	conio::clrscr();
	std::cout << "Update the current database's keys?\n\tCaution: This may take a while." << std::endl;
	if (!conio::consolePromptBool()) return;

	std::cout << "Loading old key..." << std::endl;
	std::fstream keyIn(DatabaseLocation + DIRSEP + GetDatabaseName() + DIRSEP + "key.csv");
	if (keyIn.fail()) {
		std::cout << "WARNING! 'key.csv' could not be found! Create one now?\n\tCaution: If you create a new key file, some data may be unreadable.\n\t\t" << std::flush;
		if (!conio::consolePromptBool()) { return; }
		std::cout << "Creating; " << DatabaseLocation + DIRSEP + GetDatabaseName() + DIRSEP + "key.csv" << std::endl;
		CreateNewKey();
		std::cout << "New key successfully created!" << std::endl;
		conio::pause();
		return;
	}
	char* str = new char[1000000]; //1MB
	std::vector<std::string> Key[11];
	for (int i = 0; i < 11; i++) {
		keyIn.getline(str, 1000000);
		Key[i] = SplitString(str, ",");
	}
	delete[] str;
	keyIn.close();
	std::cout << "Updating entries..." << std::endl;
	for (auto& entry : fs::directory_iterator(DatabaseLocation + DIRSEP + GetDatabaseName())) {
		std::string tmp = "." + ToLower(GetDatabaseName());
		if (entry.path().extension() != tmp) continue;
		std::vector<unsigned char> data(entry.file_size());
		int counter = 0;
		std::fstream fin(entry.path().string(), std::ios::in | std::ios::binary);
		data = adcrw::ReadFile(&fin, entry.file_size());
		fin.close();
		switch (selectedDB) {
		case DB_ITEM:
			UpdateEntry<Item>(&data, Key, entry.path().filename().string());
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

	std::fstream fout(DatabaseLocation + DIRSEP + GetDatabaseName() + DIRSEP + "key.csm");
	Key[0] = sysdat.elementList;
	Key[1] = sysdat.skilltypeList;
	Key[2] = sysdat.weapontypeList;
	Key[3] = sysdat.armortypeList;
	Key[4] = sysdat.equipmenttypeList;
	Key[5] = sysdat.itemTypeList;
	Key[6] = sysdat.itemEffectTypeList;
	Key[7] = sysdat.statusEffectList;
	Key[8] = sysdat.magicAbilityTypes;
	Key[9] = sysdat.physAbilityTypes;
	Key[10] = sysdat.passiveAbilityTypes;
	for (std::vector<std::string> vs : Key) {
		for (std::string s : vs) {
			fout << s << ",";
		}
		fout << "\n";
	}
	fout << std::flush;
	fout.close();
	DBStatus = 0;
}