#include "EditCategory.h"

Command* EditCategory::clone() const
{
	return new EditCategory(*this);
}

void EditCategory::execute(Supermarket* market) const
{
	unsigned id;
	std::cin >> id;
	try
	{
		market->editCategory(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}