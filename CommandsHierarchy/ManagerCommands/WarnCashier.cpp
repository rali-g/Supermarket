#include "WarnCashier.h"

Command* WarnCashier::clone() const
{
	return new WarnCashier(*this);
}

void WarnCashier::execute(Supermarket* market) const
{
	int cashierId = 0;
	int points = 0;
	char buffer[256];
	std::cin >> cashierId >> points;
	std::cin.ignore();
	std::cin.getline(buffer, 256);
	MyString description(buffer);
	try
	{
		market->warnCashier(cashierId, points, description);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}