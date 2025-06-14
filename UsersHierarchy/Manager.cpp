#include "Manager.h"
#include "../Components/CodeGenerator.hpp"

void Manager::generateCode()
{
	CodeGenerator* generator = new CodeGenerator;
	specialCode = generator->generateManagerCode();
	delete generator;
}

Manager::Manager(const MyString& firstName, const MyString& secondName,
	const MyString& phoneNumber, const MyString& password, int age) : Employee(firstName, secondName, phoneNumber, password, age)
{
	generateCode();
	writeCodeToFile();
}

Manager::Manager(MyString&& firstName, MyString&& secondName, MyString&& phoneNumber, MyString&& password, int age)
	: Employee(std::move(firstName), std::move(secondName), std::move(phoneNumber), std::move(password), age) {}

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

	ofs << specialCode << std::endl;

	ofs.close();
}

const MyString& Manager::readCodeFromFile()
{
	char buff[1024];
	MyString filename = MyString(uintToStr(getId(), buff)) + "_special_code.txt";

	std::ifstream ifs(filename.c_str(), std::ios::in);
	if (!ifs.is_open()) {
		throw std::runtime_error("Cannot open file!");
	}

	char line[1024];
	ifs.getline(line, 1024);

	specialCode = MyString(line);

	ifs.close();
	return specialCode;
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

UserType Manager::getUserType() const
{
	return UserType::Manager;
}

void Manager::help() const
{
	std::cout << "1. list_warned_cashiers [points]" << std::endl;
	std::cout << "2. list_pending" << std::endl;
	std::cout << "3. warn_cashier [id] [points] [description]" << std::endl;
	std::cout << "4. promote_cashier [id] [special code]" << std::endl;
	std::cout << "5. approve_registration [id] [special code]" << std::endl;
	std::cout << "6. disapprove_registration [id] [special code]" << std::endl;
	std::cout << "7. fire_cashier [id] [special code]" << std::endl;
	std::cout << "8. add_category [name] [description]" << std::endl;
	std::cout << "9. edit_category [id]" << std::endl;
	std::cout << "10. delete_category [id]" << std::endl;
	std::cout << "11. add_product [product type]" << std::endl;
	std::cout << "12. edit_product [id]" << std::endl;
	std::cout << "13. delete_product [id]" << std::endl;
	std::cout << "14. load_products [filename]" << std::endl;
	std::cout << "15. load_giftcards [filename]" << std::endl;
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
	std::cout << "=== Manager ===\n";
	printBasicInfo();
}

bool CodeGenerator::seeded = false;
