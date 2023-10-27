#include "ExportData.h"
#include "DatabaseInformation.h"
#include "DataConversion.h"

template <>
toml::table _ExportData<Item>(void) {
	Item tmp = std::get<Item>(activeEntry);
	toml::table doc = toml::table{};
	toml::table tmpTbl = toml::table{};
	toml::array tmpArrA = toml::array{};
	toml::array tmpArrB = toml::array{};

	tmpTbl.insert("ID", tmp.meta.ID);
	tmpTbl.insert("Checksum", tmp.meta.checksum);
	tmpTbl.insert("ADT", tmp.meta.datatype);
	doc.insert("meta", tmpTbl); 
	tmpTbl.clear();

	for (bool b : tmp.data.itemType) tmpArrA.push_back(b);
	tmpTbl.insert("ItemType", tmpArrA);
	tmpArrA.clear();
	tmpTbl.insert("ItemName", tmp.data.itemName);
	tmpTbl.insert("ItemDesc", tmp.data.itemDesc);
	tmpTbl.insert("ItemVal", tmp.data.itemValue);
	tmpTbl.insert("ItemWgt",tmp.data.itemWeight);
	doc.insert("data", tmpTbl);
	tmpTbl.clear();

	for (ItemEffect ie : tmp.effects) {
		for (bool b : ie.EffectFlags) tmpArrB.push_back(b);
		tmpTbl.insert("EffectFlags", tmpArrB);
		tmpArrB.clear();

		for (bool b : ie.ElementFlags) tmpArrB.push_back(b);
		tmpTbl.insert("ElementFlags", tmpArrB);
		tmpArrB.clear();

		for (bool b : ie.AfflictionFlags) tmpArrB.push_back(b);
		tmpTbl.insert("AfflictionFlags", tmpArrB);
		tmpArrB.clear();

		tmpTbl.insert("BaseDmg", ie.BaseDamage);
		tmpTbl.insert("PROC", ie.proc);
		tmpTbl.insert("Retriggers", ie.Retriggers);
		tmpTbl.insert("AbilityRef", ie.AbilityRef);
		tmpArrA.push_back(tmpTbl);
		tmpTbl.clear();
	}
	doc.insert("effects", tmpArrA);

	return doc;
}

template <>
toml::table _ExportData<Enemy>(void) {
	Enemy tmp = std::get<Enemy>(activeEntry);
	toml::table doc = toml::table{};
	toml::table tmpTblA = toml::table{};
	toml::table tmpTblB = toml::table{};
	toml::array tmpArrA = toml::array{};
	toml::array tmpArrB = toml::array{};

	tmpTblA.insert("ID", tmp.meta.ID);
	tmpTblA.insert("Checksum", tmp.meta.checksum);
	tmpTblA.insert("ADT", tmp.meta.datatype);
	doc.insert("meta", tmpTblA);
	tmpTblA.clear();

	tmpTblB.insert("STR",	tmp.base.attrib.AStr);
	tmpTblB.insert("DEX",	tmp.base.attrib.ADex);
	tmpTblB.insert("WIL",	tmp.base.attrib.AWil);
	tmpTblB.insert("FOC",	tmp.base.attrib.AFoc);
	tmpTblB.insert("END",	tmp.base.attrib.AEnd);
	tmpTblB.insert("INT",	tmp.base.attrib.AInt);
	tmpTblB.insert("VIG",	tmp.base.attrib.AVig);
	tmpTblA.insert("params",tmpTblB);
	tmpTblB.clear();
	tmpTblB.insert("ATK",	tmp.base.statBonus.BAtk);
	tmpTblB.insert("DEF",	tmp.base.statBonus.BDef);
	tmpTblB.insert("M.ATK",	tmp.base.statBonus.BMAtk);
	tmpTblB.insert("M.DEF",	tmp.base.statBonus.BMDef);
	tmpTblB.insert("SPD",	tmp.base.statBonus.BSpd);
	tmpTblB.insert("MaxHP",	tmp.base.statBonus.BHP);
	tmpTblB.insert("MaxMP",	tmp.base.statBonus.BMP);
	tmpTblB.insert("MaxSP",	tmp.base.statBonus.BSP);
	tmpTblB.insert("ACC",	tmp.base.statBonus.BAcc);
	tmpTblB.insert("EVA",	tmp.base.statBonus.BEva);
	tmpTblB.insert("LUK",	tmp.base.statBonus.BLuk);
	tmpTblA.insert("stats",	tmpTblB);
	tmpTblB.clear();
	doc.insert("baseParams", tmpTblA);
	tmpTblA.clear();

	tmpTblB.insert("STR", tmp.base.attrib.AStr);
	tmpTblB.insert("DEX", tmp.base.attrib.ADex);
	tmpTblB.insert("WIL", tmp.base.attrib.AWil);
	tmpTblB.insert("FOC", tmp.base.attrib.AFoc);
	tmpTblB.insert("END", tmp.base.attrib.AEnd);
	tmpTblB.insert("INT", tmp.base.attrib.AInt);
	tmpTblB.insert("VIG", tmp.base.attrib.AVig);
	tmpTblA.insert("params", tmpTblB);
	tmpTblB.clear();
	tmpTblB.insert("ATK", tmp.base.statBonus.BAtk);
	tmpTblB.insert("DEF", tmp.base.statBonus.BDef);
	tmpTblB.insert("M.ATK", tmp.base.statBonus.BMAtk);
	tmpTblB.insert("M.DEF", tmp.base.statBonus.BMDef);
	tmpTblB.insert("SPD", tmp.base.statBonus.BSpd);
	tmpTblB.insert("MaxHP", tmp.base.statBonus.BHP);
	tmpTblB.insert("MaxMP", tmp.base.statBonus.BMP);
	tmpTblB.insert("MaxSP", tmp.base.statBonus.BSP);
	tmpTblB.insert("ACC", tmp.base.statBonus.BAcc);
	tmpTblB.insert("EVA", tmp.base.statBonus.BEva);
	tmpTblB.insert("LUK", tmp.base.statBonus.BLuk);
	tmpTblA.insert("stats", tmpTblB);
	tmpTblB.clear();
	doc.insert("progressive", tmpTblA);
	tmpTblA.clear();

	for (std::list<int> li : tmp.ability.base) {
		for (int i : li) tmpArrB.push_back(i);
		tmpArrA.push_back(tmpArrB);
		tmpArrB.clear();
	}
	tmpTblA.insert("Basic", tmpArrA);
	tmpArrA.clear();
	for (std::list<int> li : tmp.ability.base) {
		for (int i : li) tmpArrB.push_back(i);
		tmpArrA.push_back(tmpArrB);
		tmpArrB.clear();
	}
	tmpTblA.insert("Physical", tmpArrA);
	tmpArrA.clear();
	for (std::list<int> li : tmp.ability.base) {
		for (int i : li) tmpArrB.push_back(i);
		tmpArrA.push_back(tmpArrB);
		tmpArrB.clear();
	}
	tmpTblA.insert("Magic", tmpArrA);
	tmpArrA.clear();
	for (std::list<int> li : tmp.ability.base) {
		for (int i : li) tmpArrB.push_back(i);
		tmpArrA.push_back(tmpArrB);
		tmpArrB.clear();
	}
	tmpTblA.insert("Passive", tmpArrA);
	tmpArrA.clear();
	doc.insert("Abilities", tmpTblA);
	tmpTblA.clear();

	for (DropData dd : tmp.drops) {
		tmpTblA.insert("ItemID", dd.ItemID);
		tmpTblA.insert("Quantity", dd.Quantity);
		tmpTblA.insert("DropChance", dd.DropChance);
		tmpArrA.push_back(tmpTblA);
		tmpTblA.clear();
	}
	doc.insert("Drops", tmpArrA);
	tmpArrA.clear();

	return doc;
}

void ExportData(std::string filename) {
	toml::table doc = toml::table{};
	conio::clrscr();
	std::cout << "Exporting Entry as TOML..." << std::endl;
	switch (activeEntry.index()) {
	case 0:
		doc = _ExportData<Item>();
		break;
	case 1:
		doc = _ExportData<Enemy>();
		break;
	default:
		break;
	}

	std::fstream fout(ExportLocation + "/" + filename + ".toml", std::ios::out);
	fout << doc;
	fout << std::flush;
	fout.close();
	std::cout << "Success!\n\tExport location - " << ExportLocation << "/" << filename << ".toml" << std::endl;
	conio::pause();
}

void ExportData(void) {
	conio::clrscr();
	std::cout << "Exporting Data..." << std::endl;
	std::string filename;
	switch (activeEntry.index()) {
	case 0:
		filename = std::get<Item>(activeEntry).meta.filename;
		break;

	case 1:
		filename = std::get<Enemy>(activeEntry).meta.filename;
		break;

	default:
		conio::clrscr();
		std::cerr << "\033[41m\033[93mERR: Active entry could not be read.\033[m" << std::endl;
		conio::pause();
		return;
	}

	if (filename.empty()) {
		char tmp[10000];
		std::cout << "There was no specified filename, please enter one now; " << std::endl;
		std::cout << "\tNew Value: ";
		std::cin.getline(tmp, 10000);
		std::cin.clear();
		filename = tmp;
	}

	ExportData(filename);
	return;
}