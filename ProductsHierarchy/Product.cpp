#include "Product.h"

unsigned Product::counter = 2000;

Product::Product() {
    category = new Category();
    id = counter++;
}

Product::Product(const MyString& name, const Category& category, double price)
    : productName(name), price(price) {
    this->category = new Category(category);
    id = counter++;
}

Product::Product(const Product& other)
    : productName(other.productName), price(other.price) {
    category = new Category(*other.category);
    id = other.id;
    counter = id;
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        delete category;
        productName = other.productName;
        price = other.price;
        category = new Category(*other.category);
        id = other.id;
        counter = id;
    }
    return *this;
}

Product::~Product() {
    delete category;
}

const MyString& Product::getProductName() const {
    return productName;
}

const Category& Product::getCategory() const {
    return *category;
}

double Product::getPrice() const {
    return price;
}

unsigned Product::getId() const {
    return id;
}

void Product::setProductName(const MyString& name) {
    if (name.getSize() == 0)
        throw std::invalid_argument("Product name cannot be empty.");
    productName = name;
}

void Product::setCategory(const Category& category) {
    if (this->category) delete this->category;
    this->category = new Category(category);
}

void Product::setPrice(double price) {
    if (price < 0.0)
        throw std::invalid_argument("Price cannot be negative.");
    this->price = price;
}

void Product::printBasicInfo() const {
    std::cout << "Product Name: " << productName << "\n";
    category->print();
    std::cout << "Price: " << price << " EUR\n";
    std::cout << "Id: " << id << "\n";
}

void Product::readFromFile(std::ifstream& ifs) {
    productName = readStringFromFile(ifs);
    category->readFromFile(ifs);
    ifs.read((char*)&price, sizeof(price));
    ifs.read((char*)&id, sizeof(id));
}

void Product::writeToFile(std::ofstream& ofs) const {
    writeStringToFile(ofs, productName);
    category->writeToFile(ofs);
    ofs.write((const char*)&price, sizeof(price));
    ofs.write((const char*)&id, sizeof(id));
}

void Product::edit(const MyVector<Category> categories) {
    std::cout << "\n1. Edit product name\n2. Edit category\n3. Choose from existing category\n4. Edit price\n";
}
