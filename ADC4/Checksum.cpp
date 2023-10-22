#include "Checksum.h"

int Checksum(std::vector<unsigned char>* data) {
	int sum = 0;
	for (unsigned char item : *data) sum += (int)item;
	return sum;
}