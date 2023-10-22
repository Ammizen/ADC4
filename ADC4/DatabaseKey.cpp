#include "DatabaseKey.h"
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
	std::string line;
	std::vector<std::string> tokens;
	std::fstream fin(filepath.string() + "\\.key", std::ios::in);
	if (fin.fail()) return -1;

	getline(fin, line);
	tokens = SplitString(line, ",");
	if (_CompareKeys(&tokens, &sysdat.elementList)) return 1;
	tokens.clear();

	getline(fin, line);
	tokens = SplitString(line, ",");
	if (_CompareKeys(&tokens, &sysdat.skilltypeList)) return 2;
	tokens.clear();

	getline(fin, line);
	tokens = SplitString(line, ",");
	if (_CompareKeys(&tokens, &sysdat.weapontypeList)) return 3;
	tokens.clear();

	getline(fin, line);
	tokens = SplitString(line, ",");
	if (_CompareKeys(&tokens, &sysdat.armortypeList)) return 4;
	tokens.clear();

	getline(fin, line);
	tokens = SplitString(line, ",");
	if (_CompareKeys(&tokens, &sysdat.equipmenttypeList)) return 5;

	return 0;
}