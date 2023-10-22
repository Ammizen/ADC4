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
	Item item = Item();
	std::pair<int, std::string> tmp;

	item.meta.filename = filename;

	int ptr = 0;

	memcpy(&item.meta.checksum, &indata->at(ptr), 4);
	ptr += 4;

	memcpy(&item.meta.datatype, &indata->at(ptr), 1);
	ptr += 1 + 2; //Skip 2 Bytes... ADC Ver. & Build.

	memcpy(&item.meta.ID, &indata->at(ptr), 2);
	ptr += 2;

	std::vector<unsigned char> flagBuffer(ceil((double)sysdat.itemTypeList.size() / 8.0));
	item.data.itemType = DeconstructBytes(&flagBuffer, sysdat.itemTypeList.size());
	ptr += ceil((double)sysdat.itemTypeList.size() / 8.0);

	tmp = GetString(indata, ptr);
	item.data.itemName = tmp.second;
	ptr += tmp.first;

	tmp = GetString(indata, ptr);
	item.data.itemDesc = tmp.second;
	ptr += tmp.first;

	memcpy(&item.data.itemValue, &indata->at(ptr), 4);
	ptr += 4;

	memcpy(&item.data.itemWeight, &indata->at(ptr), 2);
	ptr += 2;

	int numOfEffects = 0;
	memcpy(&numOfEffects, &indata->at(ptr), 4);
	std::list<ItemEffect> effects(numOfEffects);
	for (int i = 0; i < numOfEffects; i++) {
		effects.push_back(ParseData<ItemEffect>(indata, ptr));
		ptr += sizeof(ItemEffect);
	}

	return item;
}