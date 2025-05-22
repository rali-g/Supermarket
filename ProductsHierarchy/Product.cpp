#include "Product.h"

void Product::printBasicInfo() const
{
	std::cout << "Product Name: " << productName << std::endl;
	std::cout << "Category: ";
	category->print();
	std::cout << "Price: " << price << " BGN" << std::endl;
	std::cout << "Id: " << id;
}

Product::Product()
{
	category = new Category();

	id = counter;
	counter++;
}

Product::Product(const MyString& name, const Category& category, double price)
{
	setProductName(name);
	setCategory(category);
	setPrice(price);

	id = counter;
	counter++;
}

Product::Product(MyString&& name, Category&& category, double price)
	: productName(std::move(name)), category(new Category(std::move(category))) {
	setPrice(price);

	id = counter;
	counter++;
}

Product::Product(const Product& other)
{
	productName = other.productName;
	category = other.category;
	price = other.price;

	id = counter;
	counter++;
}

Product& Product::operator=(const Product& other)
{
	if (this != &other) {
		productName = other.productName;
		category = other.category;
		price = other.price;

		id = counter;
		counter++;
	}
	return *this;
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

unsigned Product::getId() const
{
	return id;
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

void Product::writeToFile(std::ofstream& ofs) const
{
	writeStringToFile(ofs, productName);
	category->writeToFile(ofs);
	ofs.write((const char*)&price, sizeof(price));
	ofs.write((const char*)&id, sizeof(id));
}

void Product::readFromFile(std::ifstream& ifs)
{
	productName = readStringFromFile(ifs);
	category->readFromFile(ifs);
	ifs.read((char*)&price, sizeof(price));
	ifs.read((char*)&id, sizeof(id));
}

void Product::edit() {
	std::cout << "Enter option to continue: \n";
	std::cout << "1. Edit product name: \n2. Edit category: \n3. Edit price: \n";
}

unsigned Product::counter = 2000;
