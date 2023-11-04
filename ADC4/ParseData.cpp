#include "ParseData.h"

std::vector<bool> DeconstructBytes(std::vector<unsigned char>* indata, int numFlags) {
	std::vector<bool> outdat(numFlags);
	int ref = 0;
	for (int i = 0; i < ceil((double)numFlags / 8.0); i++) {
		for (int j = 0; j < 8; j++) {
			if (ref >= numFlags) return outdat;
			outdat[ref] = (((indata->at(i) >> j) & 0b1) == 0b1) ? true : false;
		}
	}
	return outdat;
}

std::pair<int, std::string> GetString(std::vector<unsigned char>* indata, int pos) {
	std::string str;
	int len = 0;
	while ((char)indata->at(pos + len) != '\0') {
		str += (char)indata->at(pos + len);
		len++;
	}
	return { len, str };
}

template<>
ItemEffect ParseData<ItemEffect>(std::vector<unsigned char>* indata, int pos) {
	ItemEffect itemEffect = ItemEffect();
	int ptr = pos;

	itemEffect.EffectFlags.resize(sysdat.itemEffectTypeList.size());
	itemEffect.ElementFlags.resize(sysdat.elementList.size());
	itemEffect.AfflictionFlags.resize(sysdat.statusEffectList.size());

	int numFlags = sysdat.itemEffectTypeList.size() +
		sysdat.elementList.size() +
		sysdat.statusEffectList.size();
	std::vector<unsigned char> flagBuffer(ceil((double)numFlags / 8.0));
	std::vector<bool> flags = DeconstructBytes(&flagBuffer, numFlags);
	memcpy(&flagBuffer, &indata->at(ptr), ceil((double)numFlags / 8.0));

	for (int i = 0; i < sysdat.itemEffectTypeList.size(); i++) {
		itemEffect.EffectFlags[i] = flags[i];
	}

	for (int i = 0; i < sysdat.elementList.size(); i++) {
		itemEffect.ElementFlags[i] = flags[i + sysdat.itemEffectTypeList.size()];
	}

	for (int i = 0; i < sysdat.statusEffectList.size(); i++) {
		itemEffect.AfflictionFlags[i] = flags[i + sysdat.itemEffectTypeList.size() + sysdat.elementList.size()];
	}
	ptr += ceil((double)numFlags / 8.0);

	memcpy(&itemEffect.BaseDamage, &indata->at(ptr), sizeof(int32_t));
	ptr += sizeof(int32_t);

	memcpy(&itemEffect.proc, &indata->at(ptr), sizeof(float));
	ptr += sizeof(float);

	memcpy(&itemEffect.Retriggers, &indata->at(ptr), sizeof(int8_t));
	ptr += sizeof(int8_t);

	memcpy(&itemEffect.AbilityRef, &indata->at(ptr), sizeof(int16_t));

	return itemEffect;
}

template<>
Item ParseData<Item>(std::vector<unsigned char>* indata, std::string filename) {
	char* dataMem = new char[indata->size()];
	char* endPtr;
	char* string = new char[10000];
	memcpy(dataMem, indata->data(), indata->size());
	//std::copy(indata->begin(), indata->end(), dataMem);
	//memcpy(&dataMem, &indata->at(0), indata->size());

	//Dumping memory to cout
	for (unsigned char c : *indata) {
		std::cout << (int)c << " ";
	}

	conio::pause();

	int checksum;
	memcpy(&checksum, dataMem, sizeof(int));
	int ID = std::strtol(filename.substr(0, 5).c_str(), &endPtr, 10);
	std::string fn = filename.substr(6, filename.find_last_of('.') - 6);
	MetaData meta(ADT_ITEM, checksum, ID, fn);

	Item item = Item();
	item.meta = meta;
	dataMem += 7;

	int flagSize = ceil(sysdat.itemTypeList.size() / 8);
	memcpy(&item.data.itemType, dataMem, flagSize);
	dataMem += flagSize;
	
	char* ptr = string;
	bool contLoop = true;
	while (contLoop) {
		if (*dataMem == '\0') contLoop = false;
		*ptr = *dataMem;
		dataMem++;
		ptr++;
	}
	item.data.itemName = string;
	memset(string, 0, 10000);

	ptr = string;
	contLoop = true;
	while (contLoop) {
		if (*dataMem == '\0') contLoop = false;
		*ptr = *dataMem;
		dataMem++;
		ptr++;
	}
	item.data.itemDesc = string;

	unsigned int tmpValue;
	memcpy(&tmpValue, dataMem, sizeof(int));
	item.data.itemValue = reinterpret_cast<int>(&tmpValue);
	dataMem += sizeof(int);

	memcpy(&item.data.itemWeight, dataMem, sizeof(float));
	dataMem += sizeof(float);

	int listSize;
	memcpy(&listSize, dataMem, sizeof(short));
	dataMem += sizeof(short);
	std::list<ItemEffect> effects = std::list<ItemEffect>();

	item.effects = effects;
	return item;
}