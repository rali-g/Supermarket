#include "ListUserData.h"

Command* ListUserData::clone() const
{
	return new ListUserData(*this);
}

void ListUserData::execute(Supermarket* market) const
{
	try
	{
		market->listUserData();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}