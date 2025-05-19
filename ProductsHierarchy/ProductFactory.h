#pragma once
#include "Product.h"
#include "ProductsByUnit.h"
#include "ProductsByWeight.h"

class ProductFactory {
public:
	static Product* createProduct(std::ifstream& ifs);
};