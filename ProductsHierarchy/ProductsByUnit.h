#pragma once
#include "Product.h"
class ProductsByUnit : public Product
{
private:
	unsigned availableQuantity = 0;
public:
    ProductsByUnit() = default;

    ProductsByUnit(const MyString& name, const Category& category,
        double price, unsigned availableQuantity);

    ProductsByUnit(MyString&& name, Category&& category,
        double price, unsigned availableQuantity);

    unsigned getQuantity() const override;
    void setQuantity(unsigned availableQuantity) override;

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);

    void edit() override;
    void printFormatted() const override;
    void print() const override;
    Product* clone() const override;
};

