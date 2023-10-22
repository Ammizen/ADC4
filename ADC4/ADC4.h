#pragma once
#include <algorithm>
#include <any>
#include <cctype>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <list>
#include <numbers>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <thread>
#include <typeindex>
#include <typeinfo>
#include <variant>
#include <vector>
#include "conio.h"
#include "globals.h"
#include "ACDS.h"
#include "Menus.h"
#include "errors.h"

constexpr auto ADC_VERSION = 4;
constexpr auto ADC_BUILD = 3;
constexpr auto HEADER_BYTESIZE = 9;

#ifdef _WIN32
constexpr auto PLATFORM = "Windows";
#endif
#ifdef unix
constexpr auto PLATFORM = "Linux";
#endif

namespace fs = std::filesystem;

void ExitProgram(bool forceClose);