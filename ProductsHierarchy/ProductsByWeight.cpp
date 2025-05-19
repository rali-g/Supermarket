#include "ProductsByWeight.h"

ProductsByWeight::ProductsByWeight(const MyString& name, const Category& category,
    double price, double discount, double availableKilograms)
    : Product(name, category, price, discount)
{
    setAvailableKilograms(availableKilograms);
}

ProductsByWeight::ProductsByWeight(MyString&& name, Category&& category,
    double price, double discount, double availableKilograms)
    : Product(std::move(name), std::move(category), price, discount)
{
    setAvailableKilograms(availableKilograms);
}

double ProductsByWeight::getAvailableKilograms() const {
    return availableKilograms;
}

void ProductsByWeight::setAvailableKilograms(double kilograms) {
    if (kilograms <= 0.0)
        throw std::invalid_argument("Available kilograms must be greater than 0.");
    availableKilograms = kilograms;
}

void ProductsByWeight::printFormatted() const 
{
    std::cout << getProductName() << " : " << getPrice() << " : " << availableKilograms << std::endl;
}

void ProductsByWeight::print() const {
    printBasicInfo();
    std::cout << "Available: " << availableKilograms << " kg\n";
}

Product* ProductsByWeight::clone() const {
    return new ProductsByWeight(*this);
}

void ProductsByWeight::writeToFile(std::ofstream& ofs) const
{
    Product::writeToFile(ofs); 
    ofs.write((const char*)&availableKilograms, sizeof(availableKilograms));
}

void ProductsByWeight::readFromFile(std::ifstream& ifs)
{
    Product::readFromFile(ifs);
    ifs.read((char*)&availableKilograms, sizeof(availableKilograms));
}
