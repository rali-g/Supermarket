#include "Helpers.h"

void writeStringToFile(std::ofstream& ofs, const MyString& str)
{
	int len = str.getSize();
	ofs.write((const char*)&len, sizeof(len));
	ofs.write((const char*)str.c_str(), str.getSize() * sizeof(char));
}

MyString readStringFromFile(std::ifstream& ifs)
{
	int len = 0;
	ifs.read((char*)&len, sizeof(len));
	char* buff = new char[len + 1] {};
	ifs.read((char*)buff, sizeof(char) * len);
	buff[len] = '\0';
	MyString toReturn = buff;
	delete[] buff;
	return toReturn;
}

const char* uintToStr(unsigned num, char* buffer)
{
	int i = 0;
	if (num == 0) {
		buffer[i++] = '0';
		buffer[i] = '\0';
		return buffer;
	}
	while (num > 0) {
		buffer[i++] = '0' + (num % 10);
		num /= 10;
	}
	buffer[i] = '\0';
	for (int j = 0; j < i / 2; ++j) {
		std::swap(buffer[j], buffer[i - j - 1]);
	}
	return buffer;
}

