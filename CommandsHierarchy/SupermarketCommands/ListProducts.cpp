#include "ListProducts.h"

Command* ListProducts::clone() const
{
	return new ListProducts(*this);
}

void ListProducts::execute(Supermarket* market) const
{
	try
	{
		market->listProducts();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}