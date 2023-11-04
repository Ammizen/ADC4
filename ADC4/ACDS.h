#pragma once
#include <vector>
#include <string>
#include <list>
#include <variant>

#define SERIALIZABLEDATA std::variant<MetaData, Item, ItemData, ItemEffect, std::list<ItemEffect>>

enum AuliaDataType { ADT_NONE, ADT_ITEM, ADT_ENEMY };
enum AuliaDBType { DB_NONE, DB_ITEM, DB_ENEMY };

struct SystemData {
	std::vector<std::string> elementList;			//0
	std::vector<std::string> skilltypeList;			//1
	std::vector<std::string> weapontypeList;		//2
	std::vector<std::string> armortypeList;			//3
	std::vector<std::string> equipmenttypeList;		//4
	std::vector<std::string> itemTypeList;			//5
	std::vector<std::string> itemEffectTypeList;	//6
	std::vector<std::string> statusEffectList;		//7
	std::vector<std::string> magicAbilityTypes;		//8
	std::vector<std::string> physAbilityTypes;		//9
	std::vector<std::string> passiveAbilityTypes;	//10
};
struct MetaData {
	int checksum = 0;
	AuliaDataType datatype = ADT_NONE;
	int ID = -1;
	std::string filename;

	MetaData() = default;
	MetaData(const AuliaDataType& datatype) : datatype(datatype) {}
	MetaData(const AuliaDataType& datatype,
		int checksum,
		int ID,
		std::string filename) :
		datatype(datatype),
		checksum(checksum),
		ID(ID),
		filename(filename) {}
};
struct AuliaData {
	MetaData meta = MetaData();

	AuliaData() = default;
	AuliaData(const MetaData& meta) : meta(meta) {}
};
struct ItemEffect {
	std::vector<bool> EffectFlags{ false, false, false, false, false, false };
	std::vector<bool> ElementFlags;
	std::vector<bool> AfflictionFlags;
	int32_t BaseDamage = 0;
	float proc = 0;
	int8_t Retriggers = 0;
	int16_t AbilityRef = -1;

	ItemEffect() = default;
	ItemEffect(
		const std::vector<bool>& effects,
		const std::vector<bool>& elements,
		const std::vector<bool>& afflictions,
		int32_t baseDmg,
		float proc,
		int8_t retriggers,
		int16_t abilityRef
	) : EffectFlags(effects),
		ElementFlags(elements),
		AfflictionFlags(afflictions),
		BaseDamage(baseDmg),
		proc(proc),
		Retriggers(retriggers),
		AbilityRef(abilityRef) {}
};
struct ItemData {
	std::vector<bool> itemType{ false, false, false, false, false };
	std::string itemName = "";
	std::string itemDesc = "";
	unsigned int itemValue = 0;
	float itemWeight = 0.f;

	ItemData() = default;
	ItemData(
		std::vector<bool> ItemType,
		std::string itemName,
		std::string itemDesc,
		int itemValue,
		float itemWeight
	) : itemType(ItemType),
		itemName(itemName),
		itemDesc(itemDesc),
		itemValue(itemValue),
		itemWeight(itemWeight) {}
};
struct Item : AuliaData {
	MetaData meta = MetaData(ADT_ITEM);
	ItemData data = ItemData();
	std::list<ItemEffect> effects;

	Item() = default;
	Item(
		MetaData meta,
		ItemData data,
		std::list<ItemEffect> effects
	) : meta(meta),
		data(data),
		effects(effects) {}
};
struct Attributes {
	int AStr = 0;
	int ADex = 0;
	int AWil = 0;
	int AFoc = 0;
	int AEnd = 0;
	int AInt = 0;
	int AVig = 0;
};
struct Stats {
	int BAtk = 0;
	int BDef = 0;
	int BMAtk = 0;
	int BMDef = 0;
	int BSpd = 0;

	int BHP = 0;
	int BMP = 0;
	int BSP = 0;

	int BAcc = 0;
	int BEva = 0;

	int BLuk = 0;
};
struct Parameters {
	Attributes attrib = Attributes();
	Stats statBonus = Stats();
};
struct EnemyAbilities {
	std::list<std::list<int>> base;
	std::list<std::list<int>> passive;
	std::list<std::list<int>> physical;
	std::list<std::list<int>> magic;
};
struct DropData {
	int ItemID = 0;
	float DropChance = 0.0f;
	int Quantity = 0;
};
struct Enemy {
	MetaData meta = MetaData(ADT_ENEMY);
	Parameters base = Parameters();
	Parameters incr = Parameters();
	EnemyAbilities ability = EnemyAbilities();
	std::list<DropData> drops;
};

typedef std::variant<
	std::monostate,				//0
	MetaData,					//1
	Item,						//2
	ItemData,					//3
	ItemEffect,					//4
	std::list<ItemEffect>,		//5
	std::vector<bool>,			//6
	std::list<std::list<int>>,	//7
	std::list<int>,				//8
	Enemy,						//9
	Parameters,					//10
	Attributes,					//11
	Stats,						//12
	EnemyAbilities,				//13
	std::list<DropData>,		//14
	DropData,					//15
	unsigned int,				//16
	int,						//17
	int8_t,						//18
	int16_t,					//19
	float,						//20
	double,						//21
	bool,						//22
	std::string					//23
> VALUETYPES;
typedef std::variant <
	std::monostate*,			//0
	MetaData*,					//1
	Item*,						//2
	ItemData*,					//3
	ItemEffect*,				//4
	std::list<ItemEffect>*,		//5
	std::vector<bool>*,			//6
	std::list<std::list<int>>*,	//7
	std::list<int>*,			//8
	Enemy*,						//9
	Parameters*,				//10
	Attributes*,				//11
	Stats*,						//12
	EnemyAbilities*,			//13
	std::list<DropData>*,		//14
	DropData*,					//15
	unsigned int*,				//16
	int*,						//17
	int8_t*,					//18
	int16_t*,					//19
	float*,						//20
	double*,					//21
	bool*,						//22
	std::string*				//23
> VALUEPTR;

typedef std::variant<
	Item,
	Enemy
> AULIADATA;