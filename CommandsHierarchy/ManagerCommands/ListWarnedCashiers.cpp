#include "ListWarnedCashiers.h"

Command* ListWarnedCashiers::clone() const
{
	return new ListWarnedCashiers(*this);
}

void ListWarnedCashiers::execute(Supermarket* market) const
{
	unsigned points = 0;
	std::cin >> points;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for points.\n";
		return;
	}
	try
	{
		market->listWarnedCahiers(points);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}