#include "ProductFactory.h"

Product* ProductFactory::createProduct(std::ifstream& ifs)
{
	ProductType type;
	Product* ptr = nullptr;
	ifs.read((char*)&type, sizeof(type));

	switch (type) {
	case ProductType::ProductsByUnit:
		ptr = new ProductsByUnit();
		ptr->readFromFile(ifs);
		break;
	case ProductType::ProductsByWeight:
		ptr = new ProductsByWeight();
		ptr->readFromFile(ifs);
		break;
	}
	return ptr;
}