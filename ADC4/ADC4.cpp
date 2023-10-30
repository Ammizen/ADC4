#include "ADC4.h"
#include "Settings.h"

#pragma region Global Variable Initialization
SystemData sysdat = SystemData();
bool SafeMode = false;
bool CheckFailed = false;
std::string DatabaseLocation = "";
std::string ExportLocation = "";
AuliaDBType selectedDB;
AULIADATA activeEntry;
int DBStatus = 0;
int DataType = 0;
bool UnsavedChanges = false;
bool verboseMode = false;
std::monostate null = std::monostate();
#pragma endregion

#ifdef _WIN32
void StinkyWindowsConsoleSetup() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hConsole, mode);
}
#endif

int main() {
	std::cout << "Aulia Data Manager" << std::endl;
	std::cout << "\tVersion: " << ADC_VERSION << std::endl;
	std::cout << "\tBuild: " << ADC_BUILD << std::endl;
	std::cout << "\t" << PLATFORM << " Edition" << std::endl;
#if defined(_DEBUG)
	std::cout << "\tDEBUG BUILD" << std::endl;
#endif

#ifdef _WIN32
	StinkyWindowsConsoleSetup();
#endif
	
	//{Insert program startup checklist here}

	LoadSettings();

	std::cout << "Startup Complete." << std::endl;
	conio::pause();

	MainMenu();
	return 0;
}


void ExitProgram(bool forceClose) {
	if (forceClose) exit(1);
	conio::clrscr();
	std::cout << "Are you sure you want to exit?";
	if (!conio::consolePromptBool()) return;
	SaveSettings();
	exit(0);
}