#include "EditProduct.h"

Command* EditProduct::clone() const
{
	return new EditProduct(*this);
}

void EditProduct::execute(Supermarket* market) const
{
	unsigned id;
	std::cin >> id;
	try
	{
		market->editProduct(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}