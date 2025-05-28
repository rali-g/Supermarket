#include "ListEmployees.h"

Command* ListEmployees::clone() const
{
	return new ListEmployees(*this);
}

void ListEmployees::execute(Supermarket* market) const
{
	try
	{
		market->listEmployees();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}