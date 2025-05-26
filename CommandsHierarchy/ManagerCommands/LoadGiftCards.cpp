#include "LoadGiftCards.h"

Command* LoadGiftCards::clone() const
{
	return new LoadGiftCards(*this);
}

void LoadGiftCards::execute(Supermarket* market) const
{
	MyString filename;
	std::cin >> filename;
	try
	{
		market->loadGiftCards(filename);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}