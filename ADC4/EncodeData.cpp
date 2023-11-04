#include "ADC4.h"
#include "SerializeData.h"
#include "Checksum.h"

std::vector<unsigned char> EncodeData() {
	std::string StatusString = "Beginning data serialization process...";
	std::vector<unsigned char> encodedData;
	std::cout << StatusString << std::endl;
	Item item;
	Enemy enemy;
	switch (activeEntry.index()) {
	case 0:
		item = std::get<Item>(activeEntry);
		encodedData = SerializeData<Item>(&item);
		break;
	case 1:
		enemy = std::get<Enemy>(activeEntry);
		encodedData = SerializeData<Enemy>(&enemy);
	}
	return encodedData;
}