# CMakeList.txt : CMake project for ADC4, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ADC4 "ADC4.cpp" "ADC4.h" "conio.h" "globals.h" "ACDS.h" "Checksum.h" "Checksum.cpp" "CreateEntry.h" "CustomStringUtils.h" "CustomStringUtils.cpp" "DatabaseInformation.h" "DatabaseInformation.cpp" "DatabaseKey.h" "DatabaseKey.cpp" "DataConversion.h"  "DecodeData.cpp" "EncodeData.cpp" "ChangeDatabase.cpp" "CreateEntry.cpp" "DirectoryTools.h" "DirectoryTools.cpp" "EditEntryMenu.h" "EditEntryMenu.cpp" "MainMenu.cpp" "Menus.h" "ParseData.h" "ParseData.cpp"   "SaveData.h" "SaveData.cpp" "SerializeData.h" "SerializeData.cpp" "Settings.h" "Settings.cpp" "conio.cpp" "OpenEntry.h" "OpenEntry.cpp" "ImportEntry.h" "ImportEntry.cpp" "ExportData.h" "ExportData.cpp"   "adcread.h" "adcread.cpp" "errors.h" "CompileData.h" "CompileData.cpp" "ExportMenu.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ADC4 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)