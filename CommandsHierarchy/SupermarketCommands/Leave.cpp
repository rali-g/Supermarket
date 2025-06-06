#include "Leave.h"

Command* Leave::clone() const
{
	return new Leave(*this);
}

void Leave::execute(Supermarket* market) const
{
	unsigned int id = 0;
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for id. Logout aborted.\n";
		return;
	}
	try
	{
		market->leave(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}