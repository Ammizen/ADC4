#pragma once
#include "ACDS.h"

#ifdef _WIN32
#endif

#ifdef unix
//extern struct termios old, current;
#endif

extern bool CheckFailed;
extern bool SafeMode;
extern std::string DatabaseLocation;
extern std::string ExportLocation;
extern AuliaDBType selectedDB;
extern int DBStatus;
extern SystemData sysdat;
extern AULIADATA activeEntry;
extern int DataType;
extern bool UnsavedChanges;
extern bool verboseMode;
extern std::monostate null;