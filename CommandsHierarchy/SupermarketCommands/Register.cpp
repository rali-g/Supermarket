#include "Register.h"

Command* Register::clone() const
{
	return new Register(*this);
}

void Register::execute(Supermarket* market) const
{
	unsigned int age = 0;
	MyString fname;
	MyString sname;
	MyString pnumber;
	MyString passwd;
	MyString type;
	std::cin >> type >> fname >> sname >> pnumber >> age >> passwd;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for age. Registration aborted.\n";
		return;
	}
	try
	{
		market->_register(type, fname, sname, pnumber, age, passwd);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}