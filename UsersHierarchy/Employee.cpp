#include "Employee.h"
#include <iostream>
#include <fstream>

void Employee::printBasicInfo() const
{
	std::cout << "ID: " << id << '\n';
	std::cout << "First name: " << firstName << '\n';
	std::cout << "Second name: " << secondName << '\n';
	std::cout << "Phone number: " << phoneNumber << '\n';
	std::cout << "Password: " << password << '\n';
	if (age == 0) {
		std::cout << "Age: Unknown" << '\n';
	}
	else {
		std::cout << "Age: " << age << '\n';
	}
}

Employee::Employee()
{
	id = counter;
	counter++;
}

Employee::Employee(const MyString& firstName, const MyString& secondName, const MyString& password)
{
	setFirstName(firstName);
	setSecondName(secondName);
	setPassword(password);

	id = counter;
	counter++;
}

Employee::Employee(const MyString& firstName, const MyString& secondName, 
	const MyString& phoneNumber, const MyString& password, unsigned age)
{
	setFirstName(firstName);
	setSecondName(secondName);
	setPhoneNumber(phoneNumber);
	setPassword(password);
	setAge(age);

	id = counter;
	counter++;
}

Employee::Employee(MyString&& firstName, MyString&& secondName, MyString&& phoneNumber, MyString&& password, unsigned age) :
firstName(firstName), secondName(secondName), phoneNumber(phoneNumber), password(password), age(age)
{
	id = counter;
	counter++;
}

Employee::Employee(const Employee& other)
{
	firstName = other.firstName;
	secondName = other.secondName;
	phoneNumber = other.phoneNumber;
	password = other.password;
	age = other.age;

	id = other.id;
	counter = id;
}


Employee& Employee::operator=(const Employee& other)
{
	if (this != &other) {  
		firstName = other.firstName;
		secondName = other.secondName;
		phoneNumber = other.phoneNumber;
		password = other.password;
		age = other.age;

		id = other.id;
		counter = id;
	}
	return *this;
}

Employee::~Employee() = default;

bool Employee::isValidPassword(const MyString& password) const
{
	return this->password == password;
}

unsigned Employee::getId() const
{
	return id;
}

unsigned Employee::getAge() const
{
	return age;
}

const MyString& Employee::getFirstName() const
{
	return firstName;
}

const MyString& Employee::getSecondName() const
{
	return secondName;
}

const MyString& Employee::getPhoneNumber() const
{
	return phoneNumber;
}

const MyString& Employee::getPassword() const
{
	return password;
}

void Employee::setFirstName(const MyString& firstName)
{
	if (firstName.getSize() <= 0) {
		throw std::invalid_argument("Invalid first name!");
	}
	this->firstName = firstName;
}

void Employee::setSecondName(const MyString& secondName)
{
	if (secondName.getSize() <= 0) {
		throw std::invalid_argument("Invalid second name!");
	}
	this->secondName = secondName;
}

void Employee::setPhoneNumber(const MyString& phoneNumber)
{
	if (phoneNumber.getSize() <= 0) {
		throw std::invalid_argument("Invalid phoneNumber!");
	}
	this->phoneNumber = phoneNumber;
}

void Employee::setAge(unsigned age)
{
	if (age <= 0) {
		throw std::invalid_argument("Invalid age");
	}
	this->age = age;
}

void Employee::setPassword(const MyString& password)
{
	if (password.getSize() <= 0) {
		throw std::invalid_argument("Invalid password!");
	}
	this->password = password;
}

void Employee::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, firstName);
	writeStringToFile(ofs, secondName);
	writeStringToFile(ofs, phoneNumber);
	writeStringToFile(ofs, password);
	ofs.write((const char*)&age, sizeof(unsigned));
	ofs.write((const char*)&id, sizeof(unsigned));
}

void Employee::readFromFile(std::ifstream& ifs)
{
	firstName = readStringFromFile(ifs);
	secondName = readStringFromFile(ifs);
	phoneNumber = readStringFromFile(ifs);
	password = readStringFromFile(ifs);
	ifs.read((char*)&age, sizeof(unsigned));
	ifs.read((char*)&id, sizeof(unsigned));
}

unsigned Employee::counter = 1000;





