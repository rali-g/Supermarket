#include "DeleteProduct.h"

Command* DeleteProduct::clone() const
{
	return new DeleteProduct(*this);
}

void DeleteProduct::execute(Supermarket* market) const
{
	unsigned int id;
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for id.\n";
		return;
	}
	try
	{
		market->deleteProduct(id);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}