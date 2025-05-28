#include "ApproveRegistration.h"

Command* ApproveRegistration::clone() const
{
	return new ApproveRegistration(*this);
}

void ApproveRegistration::execute(Supermarket* market) const
{
	int id = 0;
	MyString specialCode;
	std::cin >> id >> specialCode;
	try
	{
		market->approveRegistration(id, specialCode);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}