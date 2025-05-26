#include "ProductsByUnit.h"

ProductsByUnit::ProductsByUnit(const MyString& name, const Category& category,
    double price, unsigned availableQuantity)
    : Product(name, category, price)
{
    setQuantity(availableQuantity);
}

ProductsByUnit::ProductsByUnit(MyString&& name, Category&& category,
    double price, unsigned availableQuantity)
    : Product(std::move(name), std::move(category), price)
{
    setQuantity(availableQuantity);
}

unsigned ProductsByUnit::getQuantity() const {
    return availableQuantity;
}

void ProductsByUnit::setQuantity(unsigned availableQuantity) {
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

void ProductsByUnit::edit(const MyVector<Category> categories)
{
    Product::edit(categories);
	std::cout << "4. Enter available quantity: \n";
	std::cout << "------Enter -1 to exit--------\n";
	MyString option;
	Category category;
	while (true) {
		std::cout << "\nEnter option: ";
		std::cin >> option;
		MyString current;
		if (option == "1") {
			std::cout << "Enter product name: ";
			std::cin >> current;
			setProductName(current);
		}
		else if (option == "2") {
			category.editCategory();
			setCategory(category);
		}
		else if (option == "3") {
			std::cout << "\nEnter category index: \n";
			for (int i = 0; i < categories.size(); i++) {
				std::cout << i << ". ";
				categories[i].print();
			}
			int ind = 0;
			std::cin >> ind;
			setCategory(categories[ind]);
		}
		else if (option == "4") {
			std::cout << "Enter price: ";
			unsigned price = 0;
			std::cin >> price;
			setPrice(price);
		}
		else if (option == "5") {
			std::cout << "Enter quantity: ";
			unsigned quantity = 0;
			std::cin >> quantity;
			setQuantity(quantity);
		}
		else if (option == "-1") {
			return;
		}
		else {
			std::cout << "Invalid option! Try again!";
			return;
		}
	}
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
