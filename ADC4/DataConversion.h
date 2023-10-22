#pragma once
#include "ADC4.h"

std::vector<unsigned char> EncodeData();
void DecodeData(fs::path filepath, std::string filename);