#pragma once
#include "ADC4.h"

void EditEntryMenu();

template <typename T>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList(T* entry) {
	return std::list<std::pair<std::string, VALUEPTR>>();
}

template <typename T>
void _EEM_EditValue(std::string name, T* entry) {
	conio::clrscr();
	std::cout << "Editing Value: " << name << std::endl;
	std::cout << "Current Value: " << *entry << std::endl;
	std::cout << "New Value: ";
	std::cin >> *entry;
	std::cin.clear();
	return;
}

template<>
void _EEM_EditValue<std::string>(std::string name, std::string* entry);

template <typename T>
void _EditEntryMenu(T entry) {
	conio::clrscr();
	std::cout << "ERROR: Undefined Behaviour.\n\tReturning to main..." << std::flush;
	conio::pause();
	return;
}

template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Item>(Item* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<MetaData>(MetaData* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<ItemData>(ItemData* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<std::list<ItemEffect>>(std::list<ItemEffect>* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<ItemEffect>(ItemEffect* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Enemy>(Enemy* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Parameters>(Parameters* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Attributes>(Attributes* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<Stats>(Stats* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<std::list<DropData>>(std::list<DropData>* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<DropData>(DropData* entry);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<EnemyAbilities>(EnemyAbilities* entry);
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList(std::list<std::list<int>>* entry, int abilityListID);
template <>
std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList<std::list<int>>(std::list<int>* entry);
//std::list<std::pair<std::string, VALUEPTR>> _EEM_GetList(std::vector<bool> entry, std::vector<std::string>* ref);