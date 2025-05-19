#pragma once
#include "GiftCard.h"
#include "SingleCategoryGiftCard.hpp"
#include "MultipleCategoryGiftCard.hpp"
#include "AllProductsGiftCard.hpp"

class GiftCardFactory {
public:
	static GiftCard* createGiftCard(std::ifstream& ifs);
};