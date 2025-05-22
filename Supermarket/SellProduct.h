#pragma once
#include "Supermarket.h"

class SellProduct {
	struct PurchasedItem {
		polymorphic_ptr<Product> product;
		double quantity;
	};
	MyVector<PurchasedItem> currProducts;
public:

	SellProduct() = default;
	void sell(Supermarket& supermarket);
};