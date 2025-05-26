#include "WarnCashier.h"

Command* WarnCashier::clone() const
{
	return new WarnCashier(*this);
}

void WarnCashier::execute(Supermarket* market) const
{
	int cashierId = 0;
	int points = 0;
	MyString description;
	std::cin >> cashierId >> points >> description;
	try
	{
		market->warnCashier(cashierId, points, description);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}