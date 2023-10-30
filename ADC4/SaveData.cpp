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
	conio::clrscr();
	fs::path dbLoc = fs::path(DatabaseLocation + DIRSEP + ToLower(GetDatabaseName()));
	
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

	while (name.empty()) {
		std::cout << "\n\tThere was no filename specified. Please specify one now: \n\t\t" << std::flush;
		std::cin >> name;
		if (name.empty()) std::cout << "\n\t\tInvalid name.";
	}
	while (ID <= 0) {
		std::cout << "\n\tThere was either an invalid ID, or no ID specified. Please correct this now;\n\t\t" << std::flush;
		std::string tmp;
		std::cin >> tmp;
		char* ptr;
		ID = std::strtol(tmp.c_str(), &ptr, 10);
		if (ID <= 0) std::cout << "\n\t\tInvalid ID.";
		for (const auto& entry : fs::directory_iterator(dbLoc)) {
			if (std::strtol(entry.path().filename().string().substr(0, 5).c_str(), &ptr, 10) != ID) continue;
			std::cout << "\n\t\t\033[93mCaution: There was another existing entry with ID matching this one.\033[m" << std::endl;
			std::cout << "\t\t\tWould you like to overwrite the conflicting entry?";
			if (conio::consolePromptBool()) {
				remove(entry.path());
				std::cout << "\t\t\tDeleted!";
				break;
			}
			std::cout << "\n\n\t\tWould you like to continue saving the conflicting entry?\n\t\t\t\033[93mCaution: If you have multiple entries that share one ID,\n\t\t\t\tit could cause problems reading the entries.\033[m" << std::flush;
			if (conio::consolePromptBool()) break;
			return;
		}
	}
	data = EncodeData();
	std::stringstream ss;
	ss << std::setw(5) << std::setfill('0') << ID;
	std::string tmp = dbLoc.string() + DIRSEP + ss.str() + "_" + name + "." + ToLower(GetDatabaseName());
	fs::path fileLoc = fs::path(tmp);
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