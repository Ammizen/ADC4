#include "ExportData.h"
#include "DatabaseInformation.h"
#include "DataConversion.h"

void CheckFolder(std::string folderName) {
	/*std::wstring wFolderName;
	wFolderName = std::wstring(folderName.begin(), folderName.end());
	if (CreateDirectory(wFolderName.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
		std::cout << "Directory successfully created!" << std::endl;
		return;
	}
	std::cout << "Failed to create directory..." << std::endl;
	return;*/

	if (fs::create_directory(folderName)) {
		std::cout << "Directory successfully created!" << std::endl;
		return;
	}
	std::cout << "Failed to create directory..." << std::endl;
	return;
}

void ExportData(fs::path exportPath) {
	std::string filename;
	std::vector<unsigned char> data;

	switch (activeEntry.index()) {
	case 0:
		filename = std::get<Item>(activeEntry).meta.filename + ".itm";
		break;
	case 1:
		filename = std::get<Enemy>(activeEntry).meta.filename + ".nme";
		break;
	}

	//Export file extentions are always 4 characters.
	if ((filename.size() - 4) == 0) {
		std::cout << "Filename in MetaData was empty!\n\tPlease specify a filename;";
		std::cin >> filename;
	}

	CheckFolder(exportPath.string());

	std::fstream file(exportPath.string() + "\\" + filename, std::ios::out | std::ios::binary);

	data = EncodeData();
	for (unsigned char foo : data) {
		file << foo;
	}
	file << std::flush;
	file.close();

	std::cout << "File saved successfully!";
	std::cout << "\tOutput file: " << DatabaseLocation + "\\item\\" + filename;
	return;
}