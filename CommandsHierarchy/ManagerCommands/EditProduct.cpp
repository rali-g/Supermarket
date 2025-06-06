#include "EditProduct.h"

Command* EditProduct::clone() const
{
	return new EditProduct(*this);
}

void EditProduct::execute(Supermarket* market) const
{
	unsigned id;
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for id.\n";
		return;
	}
	try
	{
		market->editProduct(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}