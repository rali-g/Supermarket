#pragma once
#include "../../Helpers/MyString.h"
#include "../../Helpers/Helpers.h"
#include <cstdlib>
#include <ctime> 
#include <iostream>

class CodeGenerator {
private: 
	MyString code;
    static bool seeded;

    char getRandomDigit() { return '0' + rand() % 10; }
    char getRandomUpper() { return 'A' + rand() % 26; }
    char getRandomLower() { return 'a' + rand() % 26; }

    void seedOnce() {
        if (!seeded) {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }
    }
public:
	CodeGenerator() {
        seedOnce();;
	}
	const MyString& generateManagerCode() {
        char buffer[8];
        buffer[0] = getRandomDigit();
        buffer[1] = getRandomUpper();
        buffer[2] = getRandomUpper();
        buffer[3] = getRandomDigit();
        buffer[4] = getRandomDigit();
        buffer[5] = getRandomDigit();
        buffer[6] = getRandomLower();
        buffer[7] = '\0';

        code = MyString(buffer);
        return code;
	}

    const MyString& generateCardCode(unsigned id) {
        MyString result;
        char buffer[3];
        char currBuff[1024];
        buffer[0] = getRandomDigit();
        buffer[1] = getRandomUpper();
        buffer[2] = '\0';
        result += MyString(buffer);
        result += MyString(uintToStr(id, currBuff));
        buffer[0] = getRandomUpper();
        buffer[1] = getRandomDigit();
        buffer[2] = '\0';
        result += buffer;

        code = result;
        return code;
    }
};