#include "ImportEntry.h"
#include "DataConversion.h"
bool CheckIfFileExists(std::string filename) {
	std::fstream fin(filename, std::ios::in);
	if (fin.fail()) return false;
	return true;
}

template <>
void ImportEntry<Item>(toml::table doc, std::string filename) {
	MetaData meta = MetaData(
		(AuliaDataType)doc["meta"]["ADT"].value_or(0),
		doc["meta"]["Checksum"].value_or(0),
		doc["meta"]["ID"].value_or(0),
		filename
	);
	Item newItem = Item();
	newItem.meta = meta;
	delete &meta;
	newItem.data.itemName = doc["data"]["ItemName"].value_or<std::string>("");
	newItem.data.itemDesc = doc["data"]["ItemDesc"].value_or<std::string>("");
	newItem.data.itemValue = doc["data"]["ItemVal"].value_or<int>(0);
	newItem.data.itemWeight = doc["data"]["ItemWgt"].value_or<float>(0.0f);
	doc["data"]["ItemType"].as_array()->for_each([&](auto&& elem){if constexpr (toml::is_boolean<decltype(elem)>){newItem.data.itemType.push_back(elem.get());}});
	doc["effects"].as_array()->for_each([&](auto&& elem) {
		if constexpr (toml::is_table<decltype(elem)>) {
			ItemEffect ie = ItemEffect();

			elem["EffectFlags"].as_array()->for_each([&](auto&& elem) { if constexpr (toml::is_boolean<decltype(elem)>) { ie.EffectFlags.push_back(elem.get()); }});
			elem["ElementFlags"].as_array()->for_each([&](auto&& elem) { if constexpr (toml::is_boolean<decltype(elem)>) { ie.ElementFlags.push_back(elem.get()); }});
			elem["AfflictionFlags"].as_array()->for_each([&](auto&& elem) { if constexpr (toml::is_boolean<decltype(elem)>) { ie.AfflictionFlags.push_back(elem.get()); } });
			ie.BaseDamage = elem["BaseDmg"].value_or(0);
			ie.proc = elem["PROC"].value_or(0.0f);
			ie.Retriggers = elem["Retriggers"].value_or(0);
			ie.AbilityRef = elem["AbilityRef"].value_or(0);
			newItem.effects.push_back(ie);
		}
	});
	activeEntry = newItem;
}

template <>
void ImportEntry<Enemy>(toml::table doc, std::string filename) {
	MetaData meta = MetaData(
		(AuliaDataType)doc["meta"]["ADT"].value_or(0),
		doc["meta"]["Checksum"].value_or(0),
		doc["meta"]["ID"].value_or(0),
		filename
	);
	Enemy newEnemy = Enemy();
	newEnemy.meta = meta;
	delete& meta;
	newEnemy.base.attrib.AStr = doc["baseParams"]["attrib"]["STR"].value_or<int>(0);
	newEnemy.base.attrib.ADex = doc["baseParams"]["attrib"]["DEX"].value_or<int>(0);
	newEnemy.base.attrib.AWil = doc["baseParams"]["attrib"]["WIL"].value_or<int>(0);
	newEnemy.base.attrib.AFoc = doc["baseParams"]["attrib"]["FOC"].value_or<int>(0);
	newEnemy.base.attrib.AEnd = doc["baseParams"]["attrib"]["END"].value_or<int>(0);
	newEnemy.base.attrib.AInt = doc["baseParams"]["attrib"]["INT"].value_or<int>(0);
	newEnemy.base.attrib.AVig = doc["baseParams"]["attrib"]["VIG"].value_or<int>(0);
	newEnemy.base.statBonus.BAtk = doc["baseParams"]["stats"]["ATK"].value_or<int>(0);
	newEnemy.base.statBonus.BDef = doc["baseParams"]["stats"]["DEF"].value_or<int>(0);
	newEnemy.base.statBonus.BMAtk = doc["baseParams"]["stats"]["M.ATK"].value_or<int>(0);
	newEnemy.base.statBonus.BMDef = doc["baseParams"]["stats"]["M.DEF"].value_or<int>(0);
	newEnemy.base.statBonus.BSpd = doc["baseParams"]["stats"]["SPD"].value_or<int>(0);
	newEnemy.base.statBonus.BHP = doc["baseParams"]["stats"]["MaxHP"].value_or<int>(0);
	newEnemy.base.statBonus.BMP = doc["baseParams"]["stats"]["MaxMP"].value_or<int>(0);
	newEnemy.base.statBonus.BSP = doc["baseParams"]["stats"]["MaxSP"].value_or<int>(0);
	newEnemy.base.statBonus.BAcc = doc["baseParams"]["stats"]["ACC"].value_or<int>(0);
	newEnemy.base.statBonus.BEva = doc["baseParams"]["stats"]["EVA"].value_or<int>(0);
	newEnemy.base.statBonus.BLuk = doc["baseParams"]["stats"]["LUK"].value_or<int>(0);
	newEnemy.incr.attrib.AStr = doc["progressive"]["attrib"]["STR"].value_or<int>(0);
	newEnemy.incr.attrib.ADex = doc["progressive"]["attrib"]["DEX"].value_or<int>(0);
	newEnemy.incr.attrib.AWil = doc["progressive"]["attrib"]["WIL"].value_or<int>(0);
	newEnemy.incr.attrib.AFoc = doc["progressive"]["attrib"]["FOC"].value_or<int>(0);
	newEnemy.incr.attrib.AEnd = doc["progressive"]["attrib"]["END"].value_or<int>(0);
	newEnemy.incr.attrib.AInt = doc["progressive"]["attrib"]["INT"].value_or<int>(0);
	newEnemy.incr.attrib.AVig = doc["progressive"]["attrib"]["VIG"].value_or<int>(0);
	newEnemy.incr.statBonus.BAtk = doc["progressive"]["stats"]["ATK"].value_or<int>(0);
	newEnemy.incr.statBonus.BDef = doc["progressive"]["stats"]["DEF"].value_or<int>(0);
	newEnemy.incr.statBonus.BMAtk = doc["progressive"]["stats"]["M.ATK"].value_or<int>(0);
	newEnemy.incr.statBonus.BMDef = doc["progressive"]["stats"]["M.DEF"].value_or<int>(0);
	newEnemy.incr.statBonus.BSpd = doc["progressive"]["stats"]["SPD"].value_or<int>(0);
	newEnemy.incr.statBonus.BHP = doc["progressive"]["stats"]["MaxHP"].value_or<int>(0);
	newEnemy.incr.statBonus.BMP = doc["progressive"]["stats"]["MaxMP"].value_or<int>(0);
	newEnemy.incr.statBonus.BSP = doc["progressive"]["stats"]["MaxSP"].value_or<int>(0);
	newEnemy.incr.statBonus.BAcc = doc["progressive"]["stats"]["ACC"].value_or<int>(0);
	newEnemy.incr.statBonus.BEva = doc["progressive"]["stats"]["EVA"].value_or<int>(0);
	newEnemy.incr.statBonus.BLuk = doc["progressive"]["stats"]["LUK"].value_or<int>(0);
	doc["Abilities"]["Basic"].as_array()->for_each([&](auto&& elem) {
		if constexpr (toml::is_array<decltype(elem)>) {
			std::list<int> tmp = std::list<int>();
			elem.for_each([&](auto&& elem) {if constexpr (toml::is_integer<decltype(elem)>) { tmp.push_back(elem.get()); }});
			newEnemy.ability.base.push_back(tmp);
		}
	});
	doc["Abilities"]["Physical"].as_array()->for_each([&](auto&& elem) {
		if constexpr (toml::is_array<decltype(elem)>) {
			std::list<int> tmp = std::list<int>();
			elem.for_each([&](auto&& elem) {if constexpr (toml::is_integer<decltype(elem)>) { tmp.push_back(elem.get()); }});
			newEnemy.ability.physical.push_back(tmp);
		}
	});
	doc["Abilities"]["Magic"].as_array()->for_each([&](auto&& elem) {
		if constexpr (toml::is_array<decltype(elem)>) {
			std::list<int> tmp = std::list<int>();
			elem.for_each([&](auto&& elem) {if constexpr (toml::is_integer<decltype(elem)>) { tmp.push_back(elem.get()); }});
			newEnemy.ability.magic.push_back(tmp);
		}
	});
	doc["Abilities"]["Passive"].as_array()->for_each([&](auto&& elem) {
		if constexpr (toml::is_array<decltype(elem)>) {
			std::list<int> tmp = std::list<int>();
			elem.for_each([&](auto&& elem) {if constexpr (toml::is_integer<decltype(elem)>) { tmp.push_back(elem.get()); }});
			newEnemy.ability.passive.push_back(tmp);
		}
	});
	doc["Drops"].as_array()->for_each([&](auto&& elem) {
		if constexpr (toml::is_table<decltype(elem)>) {
			DropData dd = DropData();
			dd.ItemID = elem["ItemID"].value_or(0);
			dd.Quantity = elem["Quantity"].value_or(0); 
			dd.DropChance = elem["DropChance"].value_or(0); 
			newEnemy.drops.push_back(dd); 
		}
	});
	activeEntry = newEnemy;
}

void ImportEntryMenu(void) {
	std::string filename;
	bool ExitMenu = false;
	std::string ext;
	while (!ExitMenu) {
		conio::clrscr();
		std::cout << "Please specify a file: ";
		std::cin >> filename;
		ext = filename.substr(filename.size() - 4, filename.size());
		if ((ext != "json") && (ext != "yaml") && (ext != "toml")) {
			std::cerr << "Invalid file format! Continue load anyways?";
			if (!conio::consolePromptBool()) return;
		}

		if (!CheckIfFileExists(filename)) {
			std::cout << "Specified file does not exist." << std::endl;
			conio::pause();
			return;
		}
		std::cout << "Reading data in the file..." << std::endl;
		fs::path filepath = fs::path(filename);
		std::stringstream dataIn;
		std::fstream fin(filename, std::ios::in);
		while (!fin.eof()) {
			dataIn << fin.get();
		}
		std::cout << "Finished reading, starting parsing phase..." << std::endl;
		toml::table doc;
		try {
			doc = toml::parse(dataIn);
		}
		catch (const toml::parse_error& err) {
			std::cerr << "Parsing failed!\n" << err;
			conio::pause();
			return;
		}
		switch (selectedDB) {
		case DB_ITEM:
			ImportEntry<Item>(doc, filepath.filename().string());
			break;
		case DB_ENEMY:
			//ImportEntry<Enemy>(doc, filepath.filename().string());
			break;
		default:
			return;
		}
	}
}