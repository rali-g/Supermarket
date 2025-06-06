#include "DeleteCategory.h"

Command* DeleteCategory::clone() const
{
	return new DeleteCategory(*this);
}

void DeleteCategory::execute(Supermarket* market) const
{
	unsigned id;
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for id.\n";
		return;
	}
	try
	{
		market->deleteCategory(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}