#pragma once
#include "../Helpers/MyString.h"
#include "../Helpers/Helpers.h"

enum class UserType
{
	Unknown,
	Cashier,
	Manager
};


class Employee
{
private:
	MyString firstName = "Unknown";
	MyString secondName = "Unknown";
	MyString phoneNumber = "Unknown";
	MyString password = "Unknown";
	unsigned age = 0;

	unsigned id = 0;;
	static unsigned counter;
protected:
	void printBasicInfo() const;
public:
	Employee();
	Employee(const MyString& firstName, const MyString& secondName, const MyString& password);
	Employee(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber, const MyString& password, unsigned age);
	Employee(MyString&& firstName, MyString&& secondName, MyString&& phoneNumber, MyString&& password, unsigned age);
	Employee(const Employee& other);
	Employee& operator=(const Employee& other);
	virtual ~Employee();

	bool isValidPassword(const MyString& password) const;
	virtual void whoAmI() const = 0;
	virtual void print() const = 0;
	virtual void help() const = 0;
	virtual UserType getUserType() const = 0;
	virtual Employee* clone() const = 0;

	unsigned getId() const;
	unsigned getAge() const;
	const MyString& getFirstName() const;
	const MyString& getSecondName() const;
	const MyString& getPhoneNumber() const;
	const MyString& getPassword() const;

	void setFirstName(const MyString& firstName);
	void setSecondName(const MyString& secondName);
	void setPhoneNumber(const MyString& phoneNumber);
	void setAge(unsigned age);
	void setPassword(const MyString& password);

	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;
};

