#include "ADC4.h"

template <typename T>
toml::table _ExportData(void) {
	return toml::table{};
}

template <>
toml::table _ExportData<Item>(void);
template<>
toml::table _ExportData<Enemy>(void);

void ExportData(std::string filename);
void ExportData(void);