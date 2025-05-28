#include "ListCategories.h"

Command* ListCategories::clone() const
{
	return new ListCategories(*this);
}

void ListCategories::execute(Supermarket* market) const
{
	try
	{
		market->listCategories();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}