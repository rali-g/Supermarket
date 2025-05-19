#include "GiftCardFactory.h"

GiftCard* GiftCardFactory::createGiftCard(std::ifstream& ifs)
{
    
	GiftCardType type;
	GiftCard* ptr = nullptr;
	ifs.read((char*)&type, sizeof(type));

	switch (type) {
	case GiftCardType::SingleCategoryGiftCard:
		ptr = new SingleCategoryGiftCard();
		ptr->readFromFile(ifs);
		break;
	case GiftCardType::MultipleCategoryGiftCard:
		ptr = new MultipleCategoryGiftCard();
		ptr->readFromFile(ifs);
		break;
	case GiftCardType::AllProductsGiftCard:
		ptr = new AllProductsGiftCard();
		ptr->readFromFile(ifs);
		break;
	}

	return ptr;
}
