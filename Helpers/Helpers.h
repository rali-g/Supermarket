#pragma once
#include <fstream>
#include "../Helpers/MyString.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <string>
#include <vector>
#include <cstdint>


void writeStringToFile(std::ofstream& ofs, const MyString& str);

MyString readStringFromFile(std::ifstream& ifs);

const char* uintToStr(unsigned num, char* buffer);

unsigned strToUint(const MyString& str);

const MyString& getFormattedDate();

MyString simpleSha256(const MyString& input);

MyString hashPassword(const MyString& password);