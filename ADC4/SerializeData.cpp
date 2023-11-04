#include "SerializeData.h"

std::vector<unsigned char> ToBytes(const char* dat, size_t len) {
	std::vector<unsigned char> foo(len);
//	memcpy(&foo, &dat, len);
	for (int i = 0; i < len; i++) {
		foo[i] = (unsigned char)dat[i];
	}
	return foo;
}

std::vector<unsigned char> ToBytes(std::vector<bool>* dat) {
	std::vector<unsigned char> outdat;
	for (int i = 0; i < ceil((double)dat->size() / 8.0); i++) {
		int8_t byte = 0b00000000;
		for (int j = 0; j < 8; j++) {
			byte = byte | (((int)dat->at(i) << j));
		}
		outdat.push_back(u_char(byte));
	}
	return outdat;
}

template<>
std::vector<unsigned char> SerializeData<MetaData>(MetaData* data) {
	std::vector<unsigned char> outdat;
	std::vector<unsigned char> tmp;
	outdat.push_back(u_char(data->datatype));
	outdat.push_back(u_char(ADC_VERSION));
	outdat.push_back(u_char(ADC_BUILD));
	AppendVector(&outdat, tmp);
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<ItemData>(ItemData* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, ToBytes(&data->itemType));
	AppendVector(&outdat, ToBytes(data->itemName.c_str(), data->itemName.length()));
	AppendVector(&outdat, ToBytes(data->itemDesc.c_str(), data->itemDesc.length()));
	AppendVector(&outdat, ToBytes(data->itemValue));
	AppendVector(&outdat, ToBytes(data->itemWeight));
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<ItemEffect>(ItemEffect* data) {
	std::vector<unsigned char> outdat;

	std::vector<bool> flags;
	AppendVector(&flags, data->EffectFlags);
	AppendVector(&flags, data->ElementFlags);
	AppendVector(&flags, data->AfflictionFlags);
	flags.shrink_to_fit();

	AppendVector(&outdat, ToBytes(&flags));
	AppendVector(&outdat, ToBytes((int32_t)data->BaseDamage));
	AppendVector(&outdat, ToBytes((float)data->proc));
	AppendVector(&outdat, ToBytes((int8_t)data->Retriggers));
	AppendVector(&outdat, ToBytes((int16_t)data->AbilityRef));
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<Item>(Item* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->meta));
	AppendVector(&outdat, SerializeData(&data->data));
	AppendVector(&outdat, SerializeData(&data->effects));
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<Attributes>(Attributes* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->AStr));
	AppendVector(&outdat, SerializeData(&data->ADex));
	AppendVector(&outdat, SerializeData(&data->AInt));
	AppendVector(&outdat, SerializeData(&data->AFoc));
	AppendVector(&outdat, SerializeData(&data->AVig));
	AppendVector(&outdat, SerializeData(&data->AWil));
	AppendVector(&outdat, SerializeData(&data->AEnd));
	return outdat;
}
template <>
std::vector<unsigned char> SerializeData<Stats>(Stats* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->BAtk));
	AppendVector(&outdat, SerializeData(&data->BDef));
	AppendVector(&outdat, SerializeData(&data->BMAtk));
	AppendVector(&outdat, SerializeData(&data->BMDef));
	AppendVector(&outdat, SerializeData(&data->BSpd));
	AppendVector(&outdat, SerializeData(&data->BHP));
	AppendVector(&outdat, SerializeData(&data->BMP));
	AppendVector(&outdat, SerializeData(&data->BSP));
	AppendVector(&outdat, SerializeData(&data->BAcc));
	AppendVector(&outdat, SerializeData(&data->BEva));
	AppendVector(&outdat, SerializeData(&data->BLuk));
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<Parameters>(Parameters* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->attrib));
	AppendVector(&outdat, SerializeData(&data->statBonus));
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<EnemyAbilities>(EnemyAbilities* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->base));
	AppendVector(&outdat, SerializeData(&data->physical));
	AppendVector(&outdat, SerializeData(&data->magic));
	AppendVector(&outdat, SerializeData(&data->passive));
	return outdat;
}
template <>
std::vector<unsigned char> SerializeData<DropData>(DropData* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->ItemID));
	AppendVector(&outdat, SerializeData(&data->Quantity));
	AppendVector(&outdat, SerializeData(&data->DropChance));
	return outdat;
}
template<>
std::vector<unsigned char> SerializeData<Enemy>(Enemy* data) {
	std::vector<unsigned char> outdat;
	AppendVector(&outdat, SerializeData(&data->meta));
	AppendVector(&outdat, SerializeData(&data->base));
	AppendVector(&outdat, SerializeData(&data->incr));
	AppendVector(&outdat, SerializeData(&data->ability));
	AppendVector(&outdat, SerializeData(&data->drops));
	return outdat;
}