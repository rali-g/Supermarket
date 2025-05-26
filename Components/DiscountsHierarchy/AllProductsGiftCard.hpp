#include "GiftCard.h"

class AllProductsGiftCard : public GiftCard
{
public:
	AllProductsGiftCard() = default;
	AllProductsGiftCard(double percent) : GiftCard(percent) {}

	bool meetsDiscountCriteria(const Product& product) const override {
		return true;
	}

	void getCategories() const override {
		std::cout << "All";
	}

	void writeToFile(std::ofstream& ofs) const override {
		GiftCard::writeToFile(ofs);
	}
	void readFromFile(std::ifstream& ifs) override {
		GiftCard::readFromFile(ifs);
	}

	GiftCard* clone() const override {
		return new AllProductsGiftCard(*this);
	}
	void print() const override {
		std::cout << "AllCategoryGiftCard\n";
		GiftCard::print();
	}
	void whoAmI() const override {
		std::cout << "Status: AllProductsGiftCard" << std::endl;
	}
};