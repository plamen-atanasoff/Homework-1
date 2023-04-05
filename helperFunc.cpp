#include "helperFunc.h"

size_t getSize(std::ifstream& file)
{
	unsigned int currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(currentPos, std::ios::beg);

	return size;
}
