#include "CompileData.h"
#include "DatabaseInformation.h"

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
	std::string filepath;
	long int totalBytes = 0;
	unsigned char tmpBuff[4];
	int filesize;
	fs::path dbPath(DatabaseLocation + "/" + GetDatabaseName());

	remove(filepath.c_str());
	std::fstream fout(filepath, std::ios::out | std::ios::binary);

	for (const auto& entry : std::filesystem::directory_iterator(dbPath)) {
		std::fstream fin(entry.path().string(), std::ios::in | std::ios::binary);
		fout << entry.path().filename().string().substr(0, 4);
		
		filesize = std::filesystem::file_size(entry);
		memcpy(&tmpBuff, &filesize, 4);
		fout << tmpBuff;

		while (!fin.eof()) fout << fin.get();

		fin.close();
		std::cout << "Read " << filesize << "Bytes. File ID: " << tmpBuff << std::endl;
		totalBytes += filesize;
	}

	std::cout << "\n\tFinished compiling data\n\t\tTotal bytes processed: " << totalBytes;
	conio::pause();
	return;
}