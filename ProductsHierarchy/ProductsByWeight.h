#pragma once
#include "Product.h"
class ProductsByWeight : public Product
{
private:
    unsigned availableKilograms = 0;

public:
    ProductsByWeight() = default;
    ProductsByWeight(const MyString& name, const Category& category,
        double price, unsigned availableKilograms);
    ProductsByWeight(MyString&& name, Category&& category,
        double price, unsigned availableKilograms);

    unsigned getQuantity() const override;
    void setQuantity(unsigned quantity) override;

    void edit(const MyVector<Category> categories) override;
    void printFormatted() const override;
    void print() const override;
    Product* clone() const override;

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);
};

