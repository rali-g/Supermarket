#include "PromoteCashier.h"

Command* PromoteCashier::clone() const
{
	return new PromoteCashier(*this);
}

void PromoteCashier::execute(Supermarket* market) const
{
	int cashierId = 0;
	MyString specialCode;
	std::cin >> cashierId >> specialCode;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for cashier id.\n";
		return;
	}
	try
	{
		market->promoteCashier(cashierId, specialCode);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}