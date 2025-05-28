#include "DeleteProduct.h"

Command* AddProduct::clone() const
{
	return new AddProduct(*this);
}

void AddProduct::execute(Supermarket* market) const
{
	MyString productType;
	std::cin >> productType;
	try
	{
		market->addProduct(productType);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}