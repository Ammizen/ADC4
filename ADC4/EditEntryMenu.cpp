#include "ADC4.h"
#include "EditEntryMenu.h"
#include "CreateEntry.h"

template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Item>(Item* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Meta Data", &entry->meta });
	outdat.push_back({ "Item Data", &entry->data });
	outdat.push_back({ "Item Effects", &entry->effects });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<MetaData>(MetaData* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Filename", &entry->filename });
	outdat.push_back({ "Sort ID", &entry->ID });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<ItemData>(ItemData* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Item Name", &entry->itemName });
	outdat.push_back({ "Item Type", &entry->itemType });
	outdat.push_back({ "Item Value", &entry->itemValue });
	outdat.push_back({ "Item Weight", &entry->itemWeight });
	outdat.push_back({ "Item Description", &entry->itemDesc });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<std::list<ItemEffect>>(std::list<ItemEffect>* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	std::list<ItemEffect>::iterator itr = entry->begin();
	for (int i = 0; i < entry->size(); i++) {
		outdat.push_back({ std::to_string(i), &*itr });
	}
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<ItemEffect>(ItemEffect* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Base Damage", &entry->BaseDamage });
	outdat.push_back({ "Effect Flags", &entry->EffectFlags });
	outdat.push_back({ "Element Flags", &entry->ElementFlags });
	outdat.push_back({ "Affliction Flags", &entry->AfflictionFlags });
	outdat.push_back({ "PROC", &entry->proc });
	outdat.push_back({ "Retriggers", &entry->Retriggers });
	outdat.push_back({ "Ability ID", &entry->AbilityRef });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Enemy>(Enemy* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Meta Data", &entry->meta });
	outdat.push_back({ "Base Stats", &entry->base });
	outdat.push_back({ "Incremental Stats", &entry->incr });
	outdat.push_back({ "Ability List", &entry->ability });
	outdat.push_back({ "Drops List", &entry->drops });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Parameters>(Parameters* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Attributes", &entry->attrib });
	outdat.push_back({ "Stats", &entry->statBonus });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Attributes>(Attributes* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "STR", &entry->AStr });
	outdat.push_back({ "DEX", &entry->ADex });
	outdat.push_back({ "WIL", &entry->AWil });
	outdat.push_back({ "FOC", &entry->AFoc });
	outdat.push_back({ "END", &entry->AEnd });
	outdat.push_back({ "INT", &entry->AInt });
	outdat.push_back({ "VIG", &entry->AVig });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Stats>(Stats* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Attack", &entry->BAtk });
	outdat.push_back({ "Defense", &entry->BDef });
	outdat.push_back({ "Magic Atk.", &entry->BMAtk });
	outdat.push_back({ "Magic Def.", &entry->BMDef });
	outdat.push_back({ "Speed", &entry->BSpd });
	outdat.push_back({ "Max. HP", &entry->BHP });
	outdat.push_back({ "Max. MP", &entry->BMP });
	outdat.push_back({ "Max. SP", &entry->BSP });
	outdat.push_back({ "Accuracy", &entry->BAcc });
	outdat.push_back({ "Evasion", &entry->BEva });
	outdat.push_back({ "Luck", &entry->BLuk });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<std::list<DropData>>(std::list<DropData>* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	std::string tmp;
	std::list<DropData>::iterator itr = entry->begin();
	for (int i = 0; i < entry->size(); i++) {
		tmp = std::to_string(itr->ItemID) + "x" + std::to_string(itr->Quantity) + "@" + std::to_string(itr->DropChance);
		outdat.push_back({ tmp, &*itr });
		itr++;
	}
	
	outdat.push_back({ "New Entry", &null });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<DropData>(DropData* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "ItemID", &entry->ItemID });
	outdat.push_back({ "Quantity", &entry->Quantity });
	outdat.push_back({ "Drop Chance", &entry->DropChance });
	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<EnemyAbilities>(EnemyAbilities* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	outdat.push_back({ "Base", &entry->base });
	outdat.push_back({ "Passive", &entry->base });
	outdat.push_back({ "Physical", &entry->physical });
	outdat.push_back({ "Magic", &entry->magic });
	return outdat;
}
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList(std::list<std::list<int>>* entry, int abilityListID) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;

	std::vector<std::string>* dataRef;

	switch (abilityListID) {
	case 0:
		dataRef = &sysdat.passiveAbilityTypes;
		break;
	case 1:
		dataRef = &sysdat.physAbilityTypes;
		break;
	case 2:
		dataRef = &sysdat.magicAbilityTypes;
		break;
	default:
		throw std::runtime_error("ability list index was not valid");
	}

	std::list<std::list<int>>::iterator itr = entry->begin();
	for (int i = 0; i < entry->size(); i++) {
		if (i >= dataRef->size()) { outdat.push_back({ "UNDEFINED", &*itr }); continue; }
		outdat.push_back({ dataRef->at(i), &*itr });
	}

	return outdat;
}
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<std::list<int>>(std::list<int>* entry) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	std::list<int>::iterator itr = entry->begin();
	for (int i = 0; i < entry->size(); i++) {
		outdat.push_back({ std::to_string(i), &*itr });
		itr++;
	}
	return outdat;
}
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList(std::vector<bool>* entry, std::vector<std::string>* ref) {
	std::list<std::pair<std::string, VALUEPTR>> outdat;
	for (int i = 0; i < entry->size(); i++) {
		outdat.push_back({ ref->at(i), &entry[i] });
	}
	return outdat;
}
//Fuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
template <>
void _EEM_EditValue<bool>(std::string name, bool* entry) {
	conio::clrscr();
	std::cout << "Editing Value: " << name << std::endl;
	std::cout << "Current Value: " << *entry << std::endl;
	std::cout << "Value Type: bool" << std::endl;
	std::cout << "New Value: ";
	int input;
	std::cin >> input;
	if (input) *entry = true;
	*entry = false;
	return;
}
void _EEM_EditValue(std::pair<std::string, VALUEPTR> ptrInfo, std::pair<std::string, VALUEPTR>* currentCont, std::list<std::pair<std::string, VALUEPTR>>* ptrHistory) {
	switch (ptrInfo.second.index()) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		//Navigate into the container
		if (!ptrHistory->empty()) {
			if (ptrHistory->back().second == ptrInfo.second) ptrHistory->pop_back();
			else if (ptrInfo.second != currentCont->second) {
				ptrHistory->push_back(*currentCont);
			}
		}
		else {
			ptrHistory->push_back(*currentCont);
		}
		//currentCont->second = ptrInfo.second;
		*currentCont = ptrInfo;
		return;

	case 16:
		_EEM_EditValue<int>(ptrInfo.first, std::get<int*>(ptrInfo.second));
		break;

	case 17:
		_EEM_EditValue<int8_t>(ptrInfo.first, std::get<int8_t*>(ptrInfo.second));
		break;

	case 18:
		_EEM_EditValue<int16_t>(ptrInfo.first, std::get<int16_t*>(ptrInfo.second));
		break;

	case 19:
		_EEM_EditValue<float>(ptrInfo.first, std::get<float*>(ptrInfo.second));
		break;

	case 20:
		_EEM_EditValue<double>(ptrInfo.first, std::get<double*>(ptrInfo.second));
		break;

	case 21:
		_EEM_EditValue<bool>(ptrInfo.first, std::get<bool*>(ptrInfo.second));
		break;

	case 22:
		_EEM_EditValue<std::string>(ptrInfo.first, std::get<std::string*>(ptrInfo.second));
		break;
	}
	UnsavedChanges = true;
	return;
}
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList(VALUEPTR contPtr) {
	std::list<std::pair<std::string, VALUEPTR>> data;
	switch (contPtr.index()) {
	case 1:
		data = _EEM_GetList<MetaData>(std::get<MetaData*>(contPtr));
		break;
	case 2:
		data = _EEM_GetList<Item>(std::get<Item*>(contPtr));
		break;
	case 3:
		data = _EEM_GetList<ItemData>(std::get<ItemData*>(contPtr));
		break;
	case 4:
		data = _EEM_GetList<ItemEffect>(std::get<ItemEffect*>(contPtr));
		break;
	case 5:
		data = _EEM_GetList<std::list<ItemEffect>>(std::get<std::list<ItemEffect>*>(contPtr));
		break;
	case 6:
		data = _EEM_GetList<std::vector<bool>>(std::get<std::vector<bool>*>(contPtr));
		break;
	case 7:
		data = _EEM_GetList<std::list<std::list<int>>>(std::get<std::list<std::list<int>>*>(contPtr));
		break;
	case 8:
		data = _EEM_GetList<std::list<int>>(std::get<std::list<int>*>(contPtr));
		break;
	case 9:
		data = _EEM_GetList<Enemy>(std::get<Enemy*>(contPtr));
		break;
	case 10:
		data = _EEM_GetList<Parameters>(std::get<Parameters*>(contPtr));
		break;
	case 11:
		data = _EEM_GetList<Attributes>(std::get<Attributes*>(contPtr));
		break;
	case 12:
		data = _EEM_GetList<Stats>(std::get<Stats*>(contPtr));
		break;
	case 13:
		data = _EEM_GetList<EnemyAbilities>(std::get<EnemyAbilities*>(contPtr));
		break;
	case 14:
		data = _EEM_GetList<std::list<DropData>>(std::get<std::list<DropData>*>(contPtr));
		break;
	case 15:
		data = _EEM_GetList<DropData>(std::get<DropData*>(contPtr));
		break;
	}
	return data;
}
void _EEM_MenuDisplay(std::list<std::pair<std::string, VALUEPTR>>* subentryList, std::list<std::pair<std::string, VALUEPTR>>* ptrHistory, std::pair<std::string, VALUEPTR>* currentCont) {
	int counter = 1;
	for (std::pair<std::string, VALUEPTR> a : *ptrHistory) {
		std::cout << a.first + "/";
	}
	std::cout << currentCont->first << std::endl;
	std::cout << "0. <Up>" << std::endl;


	for (std::pair<std::string, VALUEPTR> subentry : *subentryList) {
		std::cout << counter << ". " << subentry.first;
		if (subentry.second.index() > 15) { std::cout << " - "; }
		switch (subentry.second.index()) {
		case 16:
			std::cout << *std::get<int*>(subentry.second);
			break;
		case 17:
			std::cout << *std::get<int8_t*>(subentry.second);
			break;
		case 18:
			std::cout << *std::get<int16_t*>(subentry.second);
			break;
		case 19:
			std::cout << *std::get<float*>(subentry.second);
			break;
		case 20:
			std::cout << *std::get<double*>(subentry.second);
			break;
		case 21:
			std::cout << *std::get<bool*>(subentry.second);
			break;
		case 22:
			std::string * foo = std::get<std::string*>(subentry.second);
			if (foo->length() > 50) {
				std::cout << foo->substr(0, 50) << "...";
				break;
			}
			std::cout << *std::get<std::string*>(subentry.second);
			break;
		}
		std::cout << std::endl;
		counter++;
	}
	std::cout << "Q. Exit Menu" << std::endl;
	return;
}
std::pair<std::string, VALUEPTR> _EEM_MenuInput(std::list<std::pair<std::string, VALUEPTR>>* subentryList, VALUEPTR* currentCont, std::list<std::pair<std::string, VALUEPTR>>* ptrHistory, bool* ExitMenu) {
	int sel;
	std::string input;
	std::cin >> input;

	if (std::tolower(input.at(0)) == 'q') {
		*ExitMenu = true;
		return { "EXIT", *currentCont };
	}

	try {
		sel = std::stoi(input);
	}
	catch (...)
	{
		sel = -1;
	}

	if ((sel < 0) || (sel > subentryList->size())) {
		conio::invalidInput();
		return { ".", *currentCont };
	}

	if (sel == 0) {
		if (ptrHistory->empty()) return { ".", *currentCont };
		return { "..", ptrHistory->back().second };
	}

	std::list<std::pair<std::string, VALUEPTR>>::iterator itr = subentryList->begin();
	for (int i = 1; i < sel; i++) {
		if (itr == subentryList->end()) break;
		itr++;
	}
	if (itr == subentryList->end()) return { ".", *currentCont };
	return *itr;
}
template <>
void _EditEntryMenu<Item>(Item entry) {
	std::pair<std::string, VALUEPTR> currentCont = { "root", &entry };
	std::list<std::pair<std::string, VALUEPTR>> subentryList;
	std::list<std::pair<std::string, VALUEPTR>> ptrHistory;
	bool ExitMenu = false;
	while (!ExitMenu) {
		conio::clrscr();
		subentryList = _EEM_GetList(currentCont.second);
		_EEM_MenuDisplay(&subentryList, &ptrHistory, &currentCont);
		std::cout << std::flush;
		std::pair<std::string, VALUEPTR> sel = _EEM_MenuInput(&subentryList, &currentCont.second, &ptrHistory, &ExitMenu);
		if (ExitMenu) {
			if (!UnsavedChanges) return;
			std::cout << std::endl;
			std::cout << "Save Changes? (y/n)" << std::flush;
			char foo = std::tolower(conio::getch());
			while ((foo != 'y') && (foo != 'n') && (foo != '\033')) {
				conio::invalidInput();
				foo = conio::getch();
			}
			if (foo == 'y') break;
			if (foo == 'n') return;
			ExitMenu = false;
			continue;
		}
		if (sel.second.index() == std::variant_npos) continue;
		_EEM_EditValue(sel, &currentCont, &ptrHistory);
		//Pointer Info, Current Container, Pointer History
	}
	activeEntry.emplace<Item>(entry);
}
template <>
void _EditEntryMenu<Enemy>(Enemy entry) {
	std::pair<std::string, VALUEPTR> currentCont = { "root", &entry };
	std::list<std::pair<std::string, VALUEPTR>> subentryList;
	std::list<std::pair<std::string, VALUEPTR>> ptrHistory;
	bool ExitMenu = false;
	while (!ExitMenu) {
		conio::clrscr();
		subentryList = _EEM_GetList(currentCont.second);
		_EEM_MenuDisplay(&subentryList, &ptrHistory, &currentCont);
		std::cout << std::flush;
		std::pair<std::string, VALUEPTR> sel = _EEM_MenuInput(&subentryList, &currentCont.second, &ptrHistory, &ExitMenu);
		if (ExitMenu) {
			if (!UnsavedChanges) return;
			std::cout << std::endl;
			std::cout << "Save Changes? (y/n)" << std::flush;
			char foo = std::tolower(conio::getch());
			while ((foo != 'y') && (foo != 'n') && (foo != '\033')) {
				conio::invalidInput();
				foo = conio::getch();
			}
			if (foo == 'y') break;
			if (foo == 'n') return;
			ExitMenu = false;
			continue;
		}
		if (sel.second.index() == std::variant_npos) continue;
		_EEM_EditValue(sel, &currentCont, &ptrHistory);
		//Pointer Info, Current Container, Pointer History
	}
	activeEntry.emplace<Enemy>(entry);
}
void EditEntryMenu(void) {
	try {
		//Pull the activeEntry out of it's wrapper, and send to correct routine
		switch (activeEntry.index()) {
		case 0:
			_EditEntryMenu<Item>(std::get<Item>(activeEntry));
			break;
		case 1:
			_EditEntryMenu<Enemy>(std::get<Enemy>(activeEntry));
			break;
		default:
			std::cout << "Unrecognized data structure in memory.\n\tCould not open for editing." << std::endl;
			conio::pause();
			return;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Something went wrong while trying to open the editor." << std::endl;
		std::cerr << "\tTechnical Information;" << std::endl;
		std::cerr << e.what() << std::endl;
		conio::pause();
		return;
	}
}