#include "Manager.h"
#include "../Components/Users/CodeGenerator.hpp"

void Manager::generateCode()
{
	CodeGenerator* generator = new CodeGenerator;
	specialCode = generator->generateSpecialCode();
	delete generator;
}

Manager::Manager(const MyString& firstName, const MyString& secondName, const MyString& password)
	: Employee(firstName, secondName, password)
{
	generateCode();
}

Manager::Manager(const MyString& firstName, const MyString& secondName,
	const MyString& phoneNumber, const MyString& password, int age) : Employee(firstName, secondName, phoneNumber, password, age)
{
	generateCode();
}

bool Manager::isValidSpecialCode(const MyString& specialCode) const
{
	return this->specialCode == specialCode;
}

void Manager::writeCodeToFile() const
{
	char buff[1024];
	MyString filename = MyString(uintToStr(getId(), buff)) + "_special_code.txt";

	std::ofstream ofs(filename.c_str(), std::ios::out | std::ios::trunc);

	if (!ofs.is_open()) {
		throw std::runtime_error("Can not open file!");
	}

	ofs << getSpecialCode() << std::endl;

	ofs.close();
}

void Manager::writeToFile(std::ofstream& ofs) const
{
	Employee::writeToFile(ofs);
	writeStringToFile(ofs, specialCode);
}

void Manager::readFromFile(std::ifstream& ifs)
{
	Employee::readFromFile(ifs);
	specialCode = readStringFromFile(ifs);
}

const MyString& Manager::getSpecialCode() const
{
	return specialCode;
}

void Manager::whoAmI() const
{
	std::cout << "Status: Manager" << std::endl;
}

Employee* Manager::clone() const
{
	return new Manager(*this);
}

void Manager::print() const
{
	printBasicInfo();
	std::cout << "Special Code: " << getSpecialCode() << std::endl;
}

bool CodeGenerator::seeded = false;
