#include "ListProductsByCategory.h"

Command* ListProductsByCategory::clone() const
{
	return new ListProductsByCategory(*this);
}

void ListProductsByCategory::execute(Supermarket* market) const
{
	unsigned id = 0;
	std::cin >> id;
	try
	{
		market->listProductsByCategory(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}