#include "ImportEntry.h"
#include "DataConversion.h"
void ImportEntryMenu(void) {
	std::string filename;
	bool ExitMenu = false;

	while (!ExitMenu) {
		conio::clrscr();
		std::cout << "Please specify a file: ";
		std::cin >> filename;

		//if (!CheckIfFileExists(filename)) {
		//	std::cout << "Specified file does not exist." << std::endl;
		//	conio::pause();
		//	continue;
		//}
		//
		//if (!CheckIfFileValid) {
		//	std::cout << "Specified file was not valid.\n\tContinue load anyway?";
		//	if (!conio::consolePromptBool()) continue;
		//}

		fs::path filepath = fs::path(filename);
		DecodeData(filepath.parent_path(), filepath.filename().string());
		return;
	}
}