#include "OpenEntry.h"
#include "DatabaseInformation.h"
#include "adcread.h"
#include "ParseData.h"

void OpenEntryMenu(void) {
	bool ExitMenu = false;
	while (!ExitMenu) {
		top:
		conio::clrscr();
		std::cout << "Selected database:   " << GetDatabaseName() << std::endl;
		std::cout << "\t 1. ID Search      " << std::endl;
		std::cout << "\t 2. filename Search" << std::endl;
		std::cout << "\tESC Close menu     " << std::endl;

		int sel = conio::getch();
		std::string fileToOpen;
		std::string filename;
		char* endPtr;
		std::vector<unsigned char> data;
		std::fstream fin;
		std::string ssel;
		int filesize;
		switch (sel) {
		case '1':
			std::cout << "Please enter the ID of the file you wish to open; " << std::flush;
			std::cin >> sel;
			std::cin.clear();
			for (auto& entry : fs::directory_iterator(DatabaseLocation + DIRSEP + GetDatabaseName())) {
				int fID = std::strtol(entry.path().filename().string().substr(0, 5).c_str(), &endPtr, 10);
				if (fID != sel) continue;
				fileToOpen = entry.path().string();
				filename = entry.path().filename().string();
				filesize = entry.file_size();
				break;
			}
			if (fileToOpen.empty()) {
				std::cout << "Couldn't find the file ID specified!" << std::endl;
				conio::pause();
				goto top;
			}
			fin.open(fileToOpen, std::ios::in | std::ios::binary);
			data = adcrw::ReadFile(&fin, filesize);
			fin.close();
			break;
		case '2':
			std::cout << "Please enter the filename of the file you wish to open; " << std::flush;
			std::cin >> ssel;
			std::cin.clear();
			for (auto& entry : fs::directory_iterator(DatabaseLocation + DIRSEP + GetDatabaseName())) {
				if (entry.path().filename().string().substr(6, entry.path().filename().string().length())!= ssel) continue;
				fileToOpen = entry.path().string();
				filename = entry.path().filename().string();
				filesize = entry.file_size();
				break;
			}
			if (fileToOpen.empty()) {
				std::cout << "Couldn't find the file ID specified!" << std::endl;
				conio::pause();
				goto top;
			}
			fin.open(fileToOpen, std::ios::in | std::ios::binary);
			data = adcrw::ReadFile(&fin, filesize);
			fin.close();
			break;
		case '\033':
			return;
		default:
			conio::invalidInput();
			goto top;
		}

		switch (selectedDB) {
		case DB_ITEM:
			activeEntry = ParseData<Item>(&data, filename);
			break;
		case DB_ENEMY:
			activeEntry = ParseData<Enemy>(&data, filename);
			break;
		default:
			return;
		}
	}
	//Exit Menu
	return;
}