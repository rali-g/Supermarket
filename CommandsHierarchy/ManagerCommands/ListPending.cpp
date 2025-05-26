#include "ListPending.h"

Command* ListPending::clone() const
{
	return new ListPending(*this);
}

void ListPending::execute(Supermarket* market) const
{
	try
	{
		market->listPending();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}