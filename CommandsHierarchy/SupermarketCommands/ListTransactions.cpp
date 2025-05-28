#include "ListTransactions.h"

Command* ListTransactions::clone() const
{
	return new ListTransactions(*this);
}

void ListTransactions::execute(Supermarket* market) const
{
	try
	{
		market->listTransactions();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}