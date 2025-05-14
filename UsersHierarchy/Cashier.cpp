#include "Cashier.h"

Cashier::Cashier(const MyString& firstName, const MyString& secondName, 
	const MyString& password) : Employee(firstName, secondName, password) {}

Cashier::Cashier(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber,
	const MyString& password, int age, unsigned transactionCount, const MyVector<Warning>& warnings) :
	Employee(firstName, secondName, phoneNumber, password, age)
{
	setTransactionCount(transactionCount);
	setWarnings(warnings);
}

const unsigned Cashier::getTransactionCount() const
{
	return transactionCount;
}

const MyVector<Warning>& Cashier::getWarnings() const
{
	return warnings;
}

void Cashier::setTransactionCount(unsigned transactionCount)
{
	if (transactionCount < 0) {
		throw std::invalid_argument("Invalid transaction count");
	}
	this->transactionCount = transactionCount;
}

void Cashier::setWarnings(const MyVector<Warning>& warnings)
{
	this->warnings = warnings;
}

void Cashier::writeToFile(std::ofstream& ofs) const
{
	Employee::writeToFile(ofs);

	ofs.write((const char*)&transactionCount, sizeof(unsigned));

	size_t warningsCount = warnings.size();

	ofs.write((const char*)&warningsCount, sizeof(size_t));
	for (size_t i = 0; i < warningsCount; i++)
	{
		warnings[i].writeToFile(ofs);
	}
}

void Cashier::readFromFile(std::ifstream& ifs)
{
	Employee::readFromFile(ifs);

	ifs.read((char*)&transactionCount, sizeof(unsigned));

	size_t warningsCount = 0;

	ifs.read((char*)&warningsCount, sizeof(size_t));

	for (size_t i = 0; i < warningsCount; i++)
	{
		Warning temp;
		temp.readFromFile(ifs);
		warnings.push_back(std::move(temp));
	}
}

void Cashier::whoAmI() const
{
	std::cout << "Status: Cashier" << std::endl;
}

Employee* Cashier::clone() const
{
	return new Cashier(*this);
}

void Cashier::print() const
{
	std::cout << "=== Cashier ===\n";
	printBasicInfo();
	std::cout << "\nTransaction Count: " << transactionCount << "\n";

	std::cout << "\nWarnings:\n";
	if (warnings.size() == 0)
		std::cout << "  None\n";
	else {
		for (size_t i = 0; i < warnings.size(); ++i) {
			std::cout << "  Warning #" << (i + 1) << ":\n";
			warnings[i].print();
		}
	}
}
