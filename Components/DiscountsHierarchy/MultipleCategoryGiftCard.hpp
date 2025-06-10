#include "GiftCard.h"
#include "../../Helpers/MyVector.hpp"

class MultipleCategoryGiftCard : public GiftCard
{
private:
    MyVector<unsigned> categoryIds;

public:
    MultipleCategoryGiftCard() = default;

    MultipleCategoryGiftCard(double percentage, const MyVector<unsigned>& categoryIds) : GiftCard(percentage) {
        setCategoryIds(categoryIds);
    }

    bool meetsDiscountCriteria(const Product& product) const override {
        unsigned prodCategoryId = product.getCategory().getId();
        for (int i = 0; i < categoryIds.size(); i++) {
            if (prodCategoryId == categoryIds[i]) {
                return true;
            }
        }
        return false;
    }

    void setCategoryIds(const MyVector<unsigned>& categoryIds) {
        this->categoryIds = categoryIds;
    }

    const  MyVector<unsigned>& getCategoryIds() const {
        return categoryIds;
    }

    void getCategories() const override {
        for (int i = 0; i < categoryIds.size(); i++) {
            std::cout << categoryIds[i] << "\n";
        }
    }

    void writeToFile(std::ofstream& ofs) const override {
        GiftCard::writeToFile(ofs);

        size_t size = categoryIds.size();
        ofs.write((const char*)(&size), sizeof(size));

        for (int i = 0; i < categoryIds.size(); i++) {
            ofs.write((const char*)(&categoryIds[i]), sizeof(categoryIds[i]));
        }
    }

    void readFromFile(std::ifstream& ifs) override {
        GiftCard::readFromFile(ifs);

        size_t size;
        ifs.read((char*)(&size), sizeof(size));

        categoryIds.clear();
        for (size_t i = 0; i < size; ++i) {
            unsigned id;
            ifs.read((char*)(&id), sizeof(id));
            categoryIds.push_back(id);
        }
    }

    GiftCard* clone() const override {
        return new MultipleCategoryGiftCard(*this);
    }

    GiftCardType getGiftCardType() const override {
        return GiftCardType::MultipleCategoryGiftCard;
    }

    void print() const override {
        std::cout << "MultipleCategoryGiftCard\n";
        GiftCard::print();
        std::cout << "\nCategories: \n";
        for (int i = 0; i < categoryIds.size(); i++) {
            std::cout << categoryIds[i] << " ";
        }
        std::cout << std::endl;
    }

    void whoAmI() const override {
        std::cout << "Status: MultipleCategoryGiftCard" << std::endl;
    }

    void addCategory(unsigned id) {
        categoryIds.push_back(id);
    }
};
