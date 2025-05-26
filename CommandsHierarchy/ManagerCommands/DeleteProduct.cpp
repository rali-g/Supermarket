#include "DeleteProduct.h"

Command* DeleteProduct::clone() const
{
	return new DeleteProduct(*this);
}

void DeleteProduct::execute(Supermarket* market) const
{
	unsigned int id;
	std::cin >> id;
	try
	{
		market->deleteProduct(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}