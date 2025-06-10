#include "GiftCard.h"

class SingleCategoryGiftCard : public GiftCard 
{
private:
	unsigned categoryId = 0;
public:
	SingleCategoryGiftCard() = default;
	SingleCategoryGiftCard(double percentage, unsigned categoryId) : GiftCard(percentage) {
		setCategoryId(categoryId);
	}
	bool meetsDiscountCriteria(const Product& product) const override {
		if (product.getCategory().getId() == categoryId) {
			return true;
		}
		return false;
	}

	void setCategoryId(unsigned categoryId) {
		this->categoryId = categoryId;
	}

	unsigned getCategoryId() const {
		return categoryId;
	}

	void writeToFile(std::ofstream& ofs) const override {
		GiftCard::writeToFile(ofs);
		ofs.write((const char*)&categoryId, sizeof(categoryId));
	}
	void readFromFile(std::ifstream& ifs) override {
		GiftCard::readFromFile(ifs);
		ifs.read((char*)&categoryId, sizeof(categoryId));
	}

	void getCategories() const override {
		std::cout << categoryId << "\n";
	}

	GiftCard* clone() const override {
		return new SingleCategoryGiftCard(*this);
	}

	GiftCardType getGiftCardType() const override {
		return GiftCardType::SingleCategoryGiftCard;
	}
	void print() const override {
		std::cout << "SingleCategoryGiftCard\n";
		GiftCard::print();
		std::cout << std::endl << categoryId;
	}
	void whoAmI() const override {
		std::cout << "Status: SingleCategoryGiftCard" << std::endl;
	}
};