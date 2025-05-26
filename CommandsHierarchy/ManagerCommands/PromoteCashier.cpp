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
	try
	{
		market->promoteCashier(cashierId, specialCode);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}