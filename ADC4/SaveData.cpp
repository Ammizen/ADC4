#include "SaveData.h"
#include "ADC4.h"
#include "DatabaseInformation.h"
#include "DataConversion.h"
#include "CustomStringUtils.h"

void CheckDBFolder(std::string folderName) {
	if (fs::create_directory(folderName)) {
		std::cout << "Directory successfully created!" << std::endl;
		return;
	}
	std::cout << "Failed to create directory..." << std::endl;
	return;
}

void SaveData() {
	fs::path dbLoc = fs::path(DatabaseLocation + "\\" + ToLower(GetDatabaseName()));
	
	int ID;
	int clusterNum = -1;
	std::string name = "";
	std::vector<unsigned char> data;

	if (!fs::exists(dbLoc)) {
		std::cout << "\n\tDatabase does not exist...\n\t\tCreating now..." << std::endl;
		fs::create_directory(dbLoc);
	}

	switch (activeEntry.index()) {
	case 0:
		name = std::get<Item>(activeEntry).meta.filename;
		ID = std::get<Item>(activeEntry).meta.ID;
		break;
	case 1:
		name = std::get<Enemy>(activeEntry).meta.filename;
		ID = std::get<Enemy>(activeEntry).meta.ID;
		break;
	default:
		return;
	}

	if (name.empty()) {
		std::cout << "\n\tThere was no filename specified. Please specify one now: \n\t\t" << std::flush;
		std::cin >> name;
	}
	if (ID <= 0) {
		std::cout << "\n\tThere was either an invalid ID, or no ID specified. Please correct this now;\n\t\t" << std::flush;
		std::string tmp;
		std::cin >> tmp;
		char* ptr;
		ID = std::strtol(tmp.c_str(), &ptr, 10);
	}
	data = EncodeData();
	fs::path fileLoc = fs::path(dbLoc.string() + "\\" + name + "." + ToLower(GetDatabaseName()));
	//dbLoc = fs::path(DatabaseLocation + "\\" + GetDatabaseName() + ".adb");

	std::fstream fin = std::fstream(fileLoc, std::ios::in | std::ios::binary);

	int ptr = 0;
	std::vector<unsigned char> buff = std::vector<unsigned char>(4);
	int clusterSize = 0;
	//If the entry to save has an ID sorted with it
	if (ID >= 0) {
		std::fstream IDFile(DatabaseLocation + "\\SYSTEM\\" + ToLower(GetDatabaseName()) + ".idl");

		int idCheck = -1;
		clusterNum = 0;

		while (ID < idCheck) {
			//First four bytes in each entry are the ID
			for (int i = 0; i < 4; i++) {
				buff[i] = IDFile.get();
			}
			memcpy(&idCheck, buff.data(), sizeof(int));
			for (int i = 0; i < 4; i++) {
				buff[i] = IDFile.get();
			}
			memcpy(&clusterSize, buff.data(), sizeof(int));
			ptr += clusterSize;
			clusterNum++;
		}

		// Send help ;w;


	}

	//If the entry has no ID associated with it, it will get stored at the end of the .adb file.


	std::fstream fout = std::fstream(fileLoc, std::ios::out | std::ios::binary);

	for (unsigned char ch : data) {
		fout << ch;
	}
}