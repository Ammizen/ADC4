#pragma once
#include "ADC4.h"

template<typename T>
T GetSerializableData(SERIALIZABLEDATA* data) {
	T* dataout;
	dataout = std::get_if<T>(data);
	return *dataout;
}
template<typename T>
void AppendVector(std::vector<T>* dest, const std::vector<T>& src) {
	dest->insert(dest->end(), src.begin(), src.end());
}
#pragma region ToBytes()
template <typename T>
std::vector<unsigned char> ToBytes(T dat) {
	std::vector<unsigned char> foo(sizeof(T));
	memcpy(foo.data(), &dat, sizeof(dat));
	return foo;
}

std::vector<unsigned char> ToBytes(const char* dat, size_t len);
std::vector<unsigned char> ToBytes(std::vector<bool>* dat);
#pragma endregion
#pragma region SerializeData()
template<typename T>
std::vector<unsigned char> SerializeData(T* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, ToBytes<T>(data));
	return outdat;
}
template <typename T>
std::vector<unsigned char> SerializeData<std::list<T>>(std::list<T>* data) {
	std::vector<unsigned char> outdat;
	for (std::list<T> a : *data) {
		AppendVector(&outdat, SerializeData(&a, statusString));
	}
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<MetaData>(MetaData* data);
template<>
std::vector<unsigned char> SerializeData<ItemData>(ItemData* data);
template<>
std::vector<unsigned char> SerializeData<ItemEffect>(ItemEffect* data);
template<>
std::vector<unsigned char> SerializeData<Item>(Item* data);
template<>
std::vector<unsigned char> SerializeData<Attributes>(Attributes* data);

#pragma endregion