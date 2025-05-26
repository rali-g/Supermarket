#include "AddCategory.h"

Command* AddCategory::clone() const
{
	return new AddCategory(*this);
}

void AddCategory::execute(Supermarket* market) const
{
	MyString name;
	MyString description;
	std::cin >> name >> description;
	try
	{
		market->addCategory(name, description);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}