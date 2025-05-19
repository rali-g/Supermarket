#pragma once
#include "Product.h"
class ProductsByWeight : public Product
{
private:
    double availableKilograms = 0;

public:
    ProductsByWeight() = default;
    ProductsByWeight(const MyString& name, const Category& category,
        double price, double discount, double availableKilograms);
    ProductsByWeight(MyString&& name, Category&& category,
        double price, double discount, double availableKilograms);

    double getAvailableKilograms() const;
    void setAvailableKilograms(double kilograms);

    void printFormatted() const override;
    void print() const override;
    Product* clone() const override;

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);
};

