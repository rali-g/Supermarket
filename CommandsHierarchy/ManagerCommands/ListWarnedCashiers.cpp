#include "ListWarnedCashiers.h"

Command* ListWarnedCashiers::clone() const
{
	return new ListWarnedCashiers(*this);
}

void ListWarnedCashiers::execute(Supermarket* market) const
{
	unsigned points = 0;
	std::cin >> points;
	try
	{
		market->listWarnedCahiers(points);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}