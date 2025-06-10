#pragma once
#include "../UsersHierarchy/Employee.h"
#include "../Helpers/MyVector.hpp"
#include "../Components/Warning.h"
#include "../Helpers/Helpers.h"
#include "../Helpers/Queue.hpp"

class Cashier : public Employee
{
private:
	unsigned transactionCount = 0;
	MyVector<Warning> warnings;
	Queue<Severity> q;
public:
	Cashier() = default;
    Cashier(const MyString& firstName,const MyString& secondName,const MyString& phoneNumber,
        const MyString& password,int age);

	unsigned getWarningPoints() const;
	unsigned getTransactionCount() const;
	const MyVector<Warning>& getWarnings() const;
	const Queue<Severity>& getQueue() const;

	void removeElementFromQueue();
	void addElementToWarnings(const Warning& warning);

	void incrementTransactionCount();
	void setTransactionCount(unsigned transactionCount);
	void setWarnings(const MyVector<Warning>& warnings);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	UserType getUserType() const override;
	void help() const override;
	void whoAmI() const override;
	Employee* clone() const override;
	void print() const override;
};

