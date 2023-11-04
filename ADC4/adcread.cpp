#include "adcread.h"

namespace adcrw {
	std::vector<unsigned char> ReadFile(std::fstream* file) {
		file->seekg(std::ios::end);
		int filesize = file->tellg();
		file->seekg(std::ios::beg);
		std::vector<unsigned char> outdat(filesize);
		char* buffer = new char[filesize];
		file->read(buffer, filesize);
		memcpy(&outdat, &buffer, sizeof(buffer));
		return outdat;
	}

	std::vector<unsigned char> ReadFile(std::fstream* file, int filesize) {
		file->seekg(std::ios::beg);
		std::vector<unsigned char> outdat(0);
		char* buffer = new char[filesize + 1];
		file->read(buffer, filesize);
		std::cout << std::endl << std::endl;
		for (int i = 0; i < filesize; i++) {
			std::cout << (int)buffer[i] << " ";
		}
		std::cout << std::endl << std::endl;
		//buffer[filesize] = '\0';
		//memcpy(outdat.data(), &buffer, sizeof(buffer));
		std::copy(&buffer[0], &buffer[filesize], std::back_inserter(outdat));
		return outdat;
	}

	AuliaDataType GetDatatype(std::filesystem::path filepath) {
		std::string ext = filepath.extension().string();
		if (ext == "item") return ADT_ITEM;
		if (ext == "enemy") return ADT_ENEMY;
		return ADT_NONE;
	}

	AuliaDataType GetDatatype(uint8_t filetype) {
		switch (filetype) {
		case 1:
			return ADT_ITEM;
		case 2:
			return ADT_ENEMY;
		}
		return ADT_NONE;
	}

	int GetInt(std::fstream* stream) {
		if (stream->bad()) throw std::runtime_error("Bad stream");
		int outdat = 0;
		std::vector<unsigned char> tmp = std::vector<unsigned char>(4);
		for (int i = 0; i < sizeof(int); i++) tmp[i] = stream->get();
		memcpy(&outdat, tmp.data(), sizeof(int));
		return outdat;
	}
}