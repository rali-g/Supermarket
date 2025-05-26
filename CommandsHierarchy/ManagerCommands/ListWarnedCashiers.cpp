#include "ListWarnedCashiers.h"

Command* ListWarnedCashiers::clone() const
{
	return new ListWarnedCashiers(*this);
}

void ListWarnedCashiers::execute(Supermarket* market) const
{
	try
	{
		market->listWarnedCahiers();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}