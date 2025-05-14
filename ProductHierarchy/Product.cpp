#include "Product.h"

void Product::printBasicInfo() const
{
	std::cout << "Product Name: " << productName << std::endl;
	std::cout << "Category: ";
	category->print();
	std::cout << "Price: " << price << " BGN" << std::endl;
	std::cout << "Discount: " << discount << "%" << std::endl;
}

Product::Product(const MyString& name, const Category& category, double price, double discount)
{
	setProductName(name);
	setCategory(category);
	setPrice(price);
	setDiscount(discount);
}

Product::Product(MyString&& name, Category&& category, double price, double discount)
	: productName(std::move(name)), category(new Category(std::move(category))) {
	setPrice(price);
	setDiscount(discount);
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

double Product::getDiscount() const {
	return discount;
}

void Product::setProductName(const MyString& name) {
	if (name.getSize() == 0) {
		throw std::invalid_argument("Product name cannot be empty.");
	}
	productName = name;
}

void Product::setCategory(const Category& category) {
	this->category = new Category(category);
}

void Product::setPrice(double price) {
	if (price < 0.0) {
		throw std::invalid_argument("Price cannot be negative.");
	}
	this->price = price;
}

void Product::setDiscount(double discount) {
	if (discount < 0.0 || discount > 100.0) {
		throw std::invalid_argument("Discount must be between 0 and 100.");
	}
	this->discount = discount;
}

void Product::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, productName);
	category->writeToFile(ofs);
	ofs.write((const char*)&price, sizeof(price));
	ofs.write((const char*)&discount, sizeof(discount));
}

void Product::readFromFile(std::ifstream& ifs)
{
	productName = readStringFromFile(ifs);
	category->readFromFile(ifs);
	ifs.read((char*)&price, sizeof(price));
	ifs.read((char*)&discount, sizeof(discount));
}
