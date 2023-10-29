#include "DatabaseKey.h"
#include "DatabaseInformation.h"
#include "CustomStringUtils.h"

bool _CompareKeys(std::vector<std::string>* tokens, std::vector<std::string>* systemTokens) {
	if (tokens->size() != systemTokens->size()) return true;
	int tokensChecked = 0;
	for (std::string token : *tokens) {
		if (token != systemTokens->at(tokensChecked)) return true;
	}
	return false;
}

int CheckKey(std::filesystem::path filepath) {
	std::fstream keyIn(DatabaseLocation + "\\" + GetDatabaseName() + "\\key.csv");
	if (keyIn.fail()) return -1;
	char* str = new char[1000000]; //1MB
	std::vector<std::string> CachedKey[11];
	for (int i = 0; i < 11; i++) {
		keyIn.getline(str, 1000000);
		CachedKey[i] = SplitString(str, ",");
	}
	keyIn.close();
	std::vector<std::string> SystemKey[11];
	SystemKey[0] = sysdat.elementList;
	SystemKey[1] = sysdat.skilltypeList;
	SystemKey[2] = sysdat.weapontypeList;
	SystemKey[3] = sysdat.armortypeList;
	SystemKey[4] = sysdat.equipmenttypeList;
	SystemKey[5] = sysdat.itemTypeList;
	SystemKey[6] = sysdat.itemEffectTypeList;
	SystemKey[7] = sysdat.statusEffectList;
	SystemKey[8] = sysdat.magicAbilityTypes;
	SystemKey[9] = sysdat.physAbilityTypes;
	SystemKey[10] = sysdat.passiveAbilityTypes;
	for (int i = 0; i < 11; i++) {
		if (SystemKey[i].size() != CachedKey[i].size()) return 1;
		for (int j = 0; j < SystemKey[i].size(); j++) {
			if (SystemKey[i][j] != CachedKey[i][j]) return 1;
		}
	}
	return 0;
}