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
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for id.\n";
		return;
	}
	try
	{
		market->approveRegistration(id, specialCode);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}