#include "DirectoryTools.h"

namespace dirtool {
	void ADC_CreateDirectory(fs::path directoryPath) {
		if (!fs::create_directory(directoryPath)) {
			throw std::runtime_error("Error in CreateDirectory(), std::filesystem::create_directory returned an error.");
		}
		return;
	}
}