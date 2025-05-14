#pragma once
#include "Product.h"
class ProductsByUnit : public Product
{
private:
	unsigned availableQuantity = 0;
public:
    ProductsByUnit() = default;

    ProductsByUnit(const MyString& name, const Category& category,
        double price, double discount, unsigned availableQuantity);

    ProductsByUnit(MyString&& name, Category&& category,
        double price, double discount, unsigned availableQuantity);

    unsigned getAvailableQuantity() const;
    void setAvailableQuantity(unsigned availableQuantity);

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);

    void print() const override;
    Product* clone() const override;
};

