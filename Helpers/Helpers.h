#pragma once
#include <fstream>
#include "../Helpers/MyString.h"


void writeStringToFile(std::ofstream& ofs, const MyString& str);

MyString readStringFromFile(std::ifstream& ifs);

const char* uintToStr(unsigned num, char* buffer);

unsigned strToUint(const MyString& str);

const MyString& getFormattedDate();