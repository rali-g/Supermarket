#include "GiftCard.h"

class SingleCategoryGiftCard : public GiftCard 
{
private:
	unsigned categoryId = 0;
public:
	SingleCategoryGiftCard() = default;
	bool meetsDiscountCriteria(const Product& product) const override {
		if (product.getCategory().getId() == categoryId) {
			return true;
		}
		return false;
	}

	void writeToFile(std::ofstream& ofs) const override {
		GiftCard::writeToFile(ofs);
		ofs.write((const char*)&categoryId, sizeof(categoryId));
	}
	void readFromFile(std::ifstream& ifs) override {
		GiftCard::readFromFile(ifs);
		ifs.read((char*)&categoryId, sizeof(categoryId));
	}

	GiftCard* clone() const override {
		return new SingleCategoryGiftCard(*this);
	}
	void print() const override {
		GiftCard::print();
		std::cout << std::endl << categoryId;
	}
	void whoAmI() const override {
		std::cout << "Status: SingleCategoryGiftCard" << std::endl;
	}
};