#include "ADC4.h"
#include "Settings.h"
#include "DirectoryTools.h"

#pragma region Private Functions
void _LoadDefaultSettings() {
	DatabaseLocation = "./Database";
	ExportLocation = "./Export";
}

char* subString(const char* s, int index, int n) {
	char* res = new char[n + 1];
	memcpy(res, s + index, n);
	res[n] = 0;
	return res;
}
#pragma endregion

void SaveSettings() {
	std::cout << "Saving Settings... " << std::endl;
	std::fstream file("./settings.cfg", std::ios::out);

	if (file.fail()) {
		throw std::runtime_error("Failed to open settings.cfg for writing.");
	}

	file << DatabaseLocation << std::endl;
	file << ExportLocation << std::flush;

	std::cout << "Successfully saved settings." << std::endl;
	return;
}
void LoadSettings() {
	if (!fs::exists("./settings.cfg")) {
		std::cout << "settings.cfg does not exist. It will be created next time settings are saved." << std::endl;
		std::cout << "Loading default settings..." << std::endl;
		_LoadDefaultSettings();
		std::cout << "Load complete." << std::endl;
		return;
	}

	std::fstream file("./settings.cfg", std::ios::in);
	if (file.fail()) {
		std::cout << "Failed to open settings.cfg for reading." << std::endl;
		std::cout << "Loading default settings..." << std::endl;
		_LoadDefaultSettings();
		std::cout << "Load complete." << std::endl;
		return;
	}

	std::getline(file, DatabaseLocation);
	std::getline(file, ExportLocation);
}
void VerifySettings() {
	std::cout << "Verifying Settings..." << std::endl;
	std::cout << "\tVerifying Database Location... ";
	if (!fs::exists(DatabaseLocation)) {
		std::cout << "Failed;" << std::endl;
		std::cout << "\t\tDirectory does not exist. Create now? (y/n)" << std::endl;
		bool validInput = false;
		char sel;
		while (!validInput) {
			sel = tolower(conio::getch());
			if ((sel == 'y') || (sel == 'n')) validInput = true;
		}
		if (sel == 'y') {
			try
			{
				dirtool::ADC_CreateDirectory(DatabaseLocation);
			}
			catch (const std::exception& e)
			{
				std::cout << "Failed to create directory..." << std::endl;
				std::cout << "\t" << e.what() << std::endl;
				std::cout << "Reverting Settings..." << std::endl;
				if (CheckFailed) {
					std::cout << "Failed to verify settings twice, loading default configuration." << std::endl;
					_LoadDefaultSettings();
				}
				else {
					CheckFailed = true;
					LoadSettings();
				}
				return;
			}
		}
		else {
			std::cout << "Aborting directory creation, and reverting settings..." << std::endl;
			if (CheckFailed) {
				std::cout << "Failed to verify settings twice, loading default configuration." << std::endl;
				_LoadDefaultSettings();
			}
			else {
				CheckFailed = true;
				LoadSettings();
			}
		}
	}
	else {
		std::cout << "Passed!" << std::endl;
	}

	std::cout << "Verifying Export Folder..." << std::endl;
	if (!fs::exists(ExportLocation)) {
		std::cout << "Failed;" << std::endl;
		std::cout << "\t\tDirectory does not exist. Create now? (y/n)" << std::endl;
		bool validInput = false;
		char sel;
		while (!validInput) {
			sel = tolower(conio::getch());
			if ((sel == 'y') || (sel == 'n')) validInput = true;
		}
		if (sel == 'y') {
			try
			{
				dirtool::ADC_CreateDirectory(ExportLocation);
			}
			catch (const std::exception& e)
			{
				std::cout << "Failed to create directory..." << std::endl;
				std::cout << "\t" << e.what() << std::endl;
				std::cout << "Reverting Settings..." << std::endl;
				if (CheckFailed) {
					std::cout << "Failed to verify settings twice, loading default configuration." << std::endl;
					_LoadDefaultSettings();
				}
				else {
					CheckFailed = true;
					LoadSettings();
				}
				return;
			}
		}
		else {
			std::cout << "Aborting directory creation, and reverting settings..." << std::endl;
			if (CheckFailed) {
				std::cout << "Failed to verify settings twice, loading default configuration." << std::endl;
				_LoadDefaultSettings();
			}
			else {
				CheckFailed = true;
				LoadSettings();
			}
		}
	}
	else {
		std::cout << "Passed!" << std::endl;
	}

	std::cout << "All settings passed verification step." << std::endl;
	return;
}

#ifdef _WIN32
#include <Windows.h>
void _ChangePath(std::string* var) {
	std::string tmp;
	std::wstring foo;
	UINT driveLetter;

	std::cout << std::endl << "Please enter a new path: ";
	std::cin >> tmp;

	foo = std::wstring(tmp.begin(), tmp.end());
	foo = foo.substr(0, 1);
	foo += L":\\";
	const char* bar = tmp.c_str();
	const char* yeet = subString(bar, 0, 3);
	driveLetter = GetDriveType(yeet);

	if (driveLetter == DRIVE_NO_ROOT_DIR) {
		std::cout << "Invalid Drive Letter, returning to menu..." << std::endl;
		conio::pause();
		return;
	}

	if (!fs::exists(tmp)) {
		std::cout << "Folder does not exist" << std::endl;
		if (!fs::create_directory(tmp)) {
			std::cout << "Could not create directory!" << std::endl;
			conio::pause();
			return;
		}
		std::cout << "Created directory successfully!" << std::endl;
	}
	*var = tmp;
	std::cout << "Changed path successfully!" << std::endl;
	conio::pause();
	return;
}
#endif
#ifdef unix
void _ChangePath(std::string* var) {
	std::string tmp;

	std::cout << std::endl << "Please enter a new path: ";
	std::cin >> tmp;

	if (!fs::exists(tmp)) {
		std::cout << "Folder does not exist" << std::endl;
		if (!fs::create_directory(tmp)) {
			std::cout << "Could not create directory!" << std::endl;
			conio::pause();
			return;
		}
		std::cout << "Created directory successfully!" << std::endl;
	}
	*var = tmp;
	std::cout << "Changed path successfully!" << std::endl;
	conio::pause();
	return;
}
#endif

void EditSettings(void) {

	char sel;

	conio::clrscr();
	std::cout << "Options Menu" << std::endl;
	std::cout << std::endl;
	std::cout << " 1. Database Location = " << DatabaseLocation << std::endl;
	std::cout << " 2. Export Location = " << ExportLocation << std::endl;
	std::cout << "ESC Back to Main" << std::endl;

	sel = conio::getch();
	switch (sel) {
	case '1':
		_ChangePath(&DatabaseLocation);
		break;
	case '2':
		_ChangePath(&ExportLocation);
		break;

	case '\033':
		VerifySettings();
		SaveSettings();
		return;
	}
}