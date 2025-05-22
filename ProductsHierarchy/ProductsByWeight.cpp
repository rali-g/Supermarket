#include "ProductsByWeight.h"

ProductsByWeight::ProductsByWeight(const MyString& name, const Category& category,
    double price, unsigned availableKilograms)
    : Product(name, category, price)
{
	setQuantity(availableKilograms);
}

ProductsByWeight::ProductsByWeight(MyString&& name, Category&& category,
    double price, unsigned availableKilograms)
    : Product(std::move(name), std::move(category), price)
{
	setQuantity(availableKilograms);
}

unsigned ProductsByWeight::getQuantity() const {
    return availableKilograms;
}

void ProductsByWeight::setQuantity(unsigned quantity) {
    if (quantity <= 0.0)
        throw std::invalid_argument("Available kilograms must be greater than 0.");
    availableKilograms = quantity;
}

void ProductsByWeight::edit()
{
	Product::edit();
	std::cout << "4. Enter available kilograms: ";
	int option = 0;
	std::cin >> option;
	MyString current;
	if (option == 1) {
		std::cout << "Enter product name: ";
		std::cin >> current;
		setProductName(current);
	}
	else if (option == 2) {
		std::cout << "Enter category: ";
		Category category;
		category.editCategory();
		setCategory(category);
	}
	else if (option == 3) {
		std::cout << "Enter price: ";
		unsigned price = 0;
		std::cin >> price;
		setPrice(price);
	}
	else if (option == 5) {
		std::cout << "Enter kilograms: ";
		unsigned kilograms = 0;
		std::cin >> kilograms;
		setQuantity(kilograms);
	}
	else {
		"Invalid option! Try again!";
	}
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
