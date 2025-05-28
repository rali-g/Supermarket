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
	try
	{
		market->_register(type, fname, sname, pnumber, age, passwd);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}