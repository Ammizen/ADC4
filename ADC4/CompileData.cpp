#include "CompileData.h"
#include "DatabaseInformation.h"
#include "CustomStringUtils.h"

void CompileData(void) {
	conio::clrscr();
	std::cout << "Compile " << GetDatabaseName() << " library file";
	if (!conio::consolePromptBool()) {
		return;
	}

	conio::clrscr();
	std::cout << "Compiling data, this may take some time..." << std::endl;

	std::string folderName;
	std::string filename;
	fs::path filepath;
	int totalBytes = 0;
	int ID;
	unsigned char tmpBuff[4];
	int filesize;
	char* endPtr;
	fs::path dbPath(DatabaseLocation + DIRSEP + GetDatabaseName());

	filepath = fs::path(dbPath.string() + DIRSEP + "items.adc");

	if (fs::exists(filepath)) {
		remove(filepath);
		std::cout << "\tRemoved existing compiled file" << std::endl; 
	}
	std::fstream fout(filepath, std::ios::out | std::ios::binary);
	std::cout << "\tCreated file for writing @ " << dbPath.string() << std::endl;

	for (const auto& entry : std::filesystem::directory_iterator(dbPath)) {
		if (entry.path().extension() != ToLower("." + GetDatabaseName())) continue;
		std::fstream fin(entry.path().string(), std::ios::in | std::ios::binary);

		ID = std::strtol(entry.path().filename().string().substr(0, 5).c_str(), &endPtr, 10);
		memcpy(&tmpBuff, &ID, 4);
		for (int i = 3; i >= 0; i--) {
			fout << tmpBuff[i];
		}
		filename = entry.path().filename().string();
		filesize = std::filesystem::file_size(entry);
		memcpy(&tmpBuff, &filesize, 4);
		for (int i = 3; i >= 0; i--) {
			fout << tmpBuff[i];
		}
		while (!fin.eof()) fout << (unsigned char)fin.get();
		fin.close();
		std::cout << "\tRead " << filesize << "Bytes. File ID: " << filename.substr(0, 5) << std::endl; 
		totalBytes += filesize + 8;
	}

	fout << std::flush;
	fout.close();
	std::cout << "\n\tFinished compiling data\n\t\tTotal bytes processed: " << totalBytes;
	conio::pause();
	return;
}