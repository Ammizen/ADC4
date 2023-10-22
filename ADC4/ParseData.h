#pragma once
#include "ADC4.h"

std::vector<bool> DeconstructBytes(std::vector<unsigned char>* indata, int numFlags);
std::pair<int, std::string> GetString(std::vector<unsigned char>* indata, int pos);
#pragma region ParseData()
template<typename T>
T ParseData(std::vector<unsigned char>* indata) {
	return T();
}

template<typename T>
T ParseData(std::vector<unsigned char>* indata, int pos) {
	return T();
}

template<typename T>
T ParseData(std::vector<unsigned char>* indata, std::string filename) {
	return T();
}

template<>
ItemEffect ParseData<ItemEffect>(std::vector<unsigned char>* indata, int pos);
template<>
Item ParseData<Item>(std::vector<unsigned char>* indata, std::string filename);
#pragma endregion