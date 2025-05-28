#include "Leave.h"

Command* Leave::clone() const
{
	return new Leave(*this);
}

void Leave::execute(Supermarket* market) const
{
	unsigned int id = 0;
	std::cin >> id;
	try
	{
		market->leave(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}