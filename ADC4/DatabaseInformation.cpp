#include "ADC4.h"

std::string GetDatabaseName(void) {
	switch (selectedDB) {
	case DB_ITEM:
		return "ITEM";
	case DB_ENEMY:
		return "ENEMY";
	}
	return "NONE";
}