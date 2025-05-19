#include "ProductsByUnit.h"

ProductsByUnit::ProductsByUnit(const MyString& name, const Category& category,
    double price, double discount, unsigned availableQuantity)
    : Product(name, category, price, discount)
{
    setAvailableQuantity(availableQuantity);
}

ProductsByUnit::ProductsByUnit(MyString&& name, Category&& category,
    double price, double discount, unsigned availableQuantity)
    : Product(std::move(name), std::move(category), price, discount)
{
    setAvailableQuantity(availableQuantity);
}

unsigned ProductsByUnit::getAvailableQuantity() const {
    return availableQuantity;
}

void ProductsByUnit::setAvailableQuantity(unsigned availableQuantity) {
    if (availableQuantity == 0)
        throw std::invalid_argument("Quantity must be greater than 0.");
    this->availableQuantity = availableQuantity;
}

void ProductsByUnit::writeToFile(std::ofstream& ofs) const
{
    Product::writeToFile(ofs);
    ofs.write((const char*)&availableQuantity, sizeof(availableQuantity));
}

void ProductsByUnit::readFromFile(std::ifstream& ifs)
{
    Product::readFromFile(ifs);
    ifs.read((char*)&availableQuantity, sizeof(availableQuantity));
}

void ProductsByUnit::printFormatted() const
{
    std::cout << getProductName() << " : " << getPrice() << " : " << availableQuantity << std::endl;
}

void ProductsByUnit::print() const {
    printBasicInfo();
    std::cout << "Quantity: " << availableQuantity;
}

Product* ProductsByUnit::clone() const {
    return new ProductsByUnit(*this);
}
