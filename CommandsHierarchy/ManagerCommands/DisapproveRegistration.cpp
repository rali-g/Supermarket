#include "DisapproveRegistration.h"

Command* DisapproveRegistration::clone() const
{
	return new DisapproveRegistration(*this);
}

void DisapproveRegistration::execute(Supermarket* market) const
{
	int id = 0;
	MyString specialCode;
	std::cin >> cashierId >> specialCode;
	try
	{
		market->disapproveRegistration(id, specialCode);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}