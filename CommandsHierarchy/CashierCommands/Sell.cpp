#include "Sell.h"

Command* Sell::clone() const
{
	return new Sell(*this);
}

void Sell::execute(Supermarket* market) const
{
	try
	{
		market->sell();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}