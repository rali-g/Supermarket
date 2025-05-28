#include "FireCashier.h"

Command* FireCashier::clone() const
{
	return new FireCashier(*this);
}

void FireCashier::execute(Supermarket* market) const
{
	int id = 0;
	MyString specialCode;
	std::cin >> id >> specialCode;
	try
	{
		market->fireCashier(id, specialCode);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}