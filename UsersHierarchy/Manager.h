#pragma once
#include "../UsersHierarchy/Employee.h"
#include "../Components/CodeGenerator.hpp"
#include "../Helpers/Helpers.h"
#include "../../UsersHierarchy/Cashier.h"

class Manager : public Employee
{
private:
	MyString specialCode = "Unknown";
	void generateCode();
public:
	Manager() = default;
	Manager(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber,
		const MyString& password, int age);
	Manager(MyString&& firstName, MyString&& secondName, MyString&& phoneNumber,
		MyString&& password, int age);

	bool isValidSpecialCode(const MyString& specialCode) const;

	void writeCodeToFile() const;
	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	const MyString& getSpecialCode() const;

	void whoAmI() const override;
	Employee* clone() const override;
	void print() const override;
};

