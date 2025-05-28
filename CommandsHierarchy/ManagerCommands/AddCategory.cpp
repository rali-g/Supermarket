#include "AddCategory.h"

Command* AddCategory::clone() const
{
	return new AddCategory(*this);
}

void AddCategory::execute(Supermarket* market) const
{
	MyString name;
	MyString description;

	char buffer[1024];

	std::cin >> buffer;
	name = MyString(buffer);

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cin.getline(buffer, 1024);
	description = MyString(buffer);

	try
	{
		market->addCategory(name, description);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}