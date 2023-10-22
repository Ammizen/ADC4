#include "CustomStringUtils.h"

std::vector<std::string> SplitString(std::string str, std::string delim) {
	std::vector<std::string> outdat;
	size_t pos = 0;
	while ((pos = str.find(delim)) != std::string::npos) {
		outdat.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
	}
	outdat.shrink_to_fit();
	return outdat;
}

std::string ToLower(std::string str) {
	std::string outdat;
	for (char c : str) {
		outdat += std::tolower(c);
	}
	return outdat;
}