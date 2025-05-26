#include "DeleteCategory.h"

Command* DeleteCategory::clone() const
{
	return new DeleteCategory(*this);
}

void DeleteCategory::execute(Supermarket* market) const
{
	unsigned id;
	std::cin >> id;
	try
	{
		market->deleteCategory(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}