#include "LoadProducts.h"

Command* LoadProducts::clone() const
{
	return new LoadProducts(*this);
}

void LoadProducts::execute(Supermarket* market) const
{
	MyString filename;
	std::cin >> filename;
	try
	{
		market->loadProducts(filename);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}