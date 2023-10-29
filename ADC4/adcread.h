#include "ADC4.h"

namespace adcrw {
	std::vector<unsigned char> ReadFile(std::fstream* file);
	std::vector<unsigned char> ReadFile(std::fstream* file, int filesize);
	AuliaDataType GetDatatype(std::filesystem::path filepath);
	AuliaDataType GetDatatype(uint8_t filetype);
	int GetInt(std::fstream* stream);
}