#include "ListGiftCards.h"

Command* ListGiftCards::clone() const
{
	return new ListGiftCards(*this);
}

void ListGiftCards::execute(Supermarket* market) const
{
	try
	{
		market->listGiftCards();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}