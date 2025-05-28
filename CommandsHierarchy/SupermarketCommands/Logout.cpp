#include "Logout.h"

Command* Logout::clone() const
{
	return new Logout(*this);
}

void Logout::execute(Supermarket* market) const
{
	try
	{
		market->logout();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}