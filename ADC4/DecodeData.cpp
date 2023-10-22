#include "ADC4.h"
#include "DataConversion.h"
#include "CustomStringUtils.h"
#include "Checksum.h"
#include "DatabaseKey.h"
#include "adcread.h"
#include "ParseData.h"

void DecodeData(fs::path filepath, std::string filename) {
	std::cout << "Beginning Decoding Process..." << std::endl;

	std::cout << "Loading data from file; " << filename << "." << std::flush;
	std::fstream file(filepath.string() + filename, std::ios::in | std::ios::binary);
	std::cout << "." << std::flush;
	std::vector<unsigned char> data = adcrw::ReadFile(&file);
	std::cout << ". Load complete!" << std::endl;

	std::cout << "Separating header from payload... " << std::flush;
	std::vector<unsigned char> header(HEADER_BYTESIZE);
	std::vector<unsigned char> payload(data.size() - HEADER_BYTESIZE);
	memcpy(&data, &header, HEADER_BYTESIZE);
	memcpy(&data[HEADER_BYTESIZE - 1], &payload, sizeof(data) - HEADER_BYTESIZE);
	std::cout << "Complete!" << std::endl;

	std::cout << "Reading Checksum... " << std::flush;
	uint32_t checksum_s = 0;
	uint32_t checksum_c = 0;
	memcpy(&header[0], &checksum_s, 4);
	checksum_c = Checksum(&payload);
	if (checksum_c != checksum_s) {
		std::cout << "Failed.\n\tChecksum mismatch, data may be corrupt. Continue operation?";
		if (!conio::consolePromptBool()) {
			std::cout << "\tAborting operation..." << std::endl;
			return;
		}
		std::cout << "\tContinuing operation..." << std::endl;
	}
	else std::cout << "Complete!" << std::endl;

	std::cout << "Checking datatype... " << std::flush;
	AuliaDataType filetype_s = adcrw::GetDatatype(header[4]);
	AuliaDataType filetype_c = adcrw::GetDatatype(filename);
	if (filetype_c != filetype_s) {
		std::cout << "Failed.\n\tFiletype mismatch, data may be corrupt. Continue operation?";
		if (!conio::consolePromptBool()) {
			std::cout << "\tAborting operation..." << std::endl;
			return;
		}
		std::cout << "\tContinuing operation..." << std::endl;
	}
	else std::cout << "Complete!" << std::endl;

	std::cout << "Checking ADC compatibility... " << std::flush;
	uint8_t progVersion_s = 0;
	uint8_t progBuild_s = 0;
	progVersion_s = header[5];
	progBuild_s = header[6];
	if ((progVersion_s != ADC_VERSION) || (progBuild_s != ADC_BUILD)) {
		std::cout << "Failed.\n\tVersion/Build mismatch, data may not be parsed correctly. Continue operation?";
		if (!conio::consolePromptBool()) {
			std::cout << "\tAborting operation..." << std::endl;
			return;
		}
		std::cout << "\tContinuing operation..." << std::endl;
	}
	else std::cout << "Complete!" << std::endl;

	std::cout << "Beginning Parsing Phase." << std::endl;
	AULIADATA dataout;
	switch ((filetype_s) ? filetype_s : filetype_c) {
	case 1:
		std::cout << "\tStructure to parse: Item" << std::endl;
		dataout = ParseData<Item>(&data);
		break;
	case 0:
	default:
		std::cout << "\tUnable to determine structure to parse. Aborting operation." << std::endl;
		return;
	}

	activeEntry = dataout;
	return;
}