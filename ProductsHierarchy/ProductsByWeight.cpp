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

void ProductsByWeight::edit(const MyVector<Category> categories)
{
	Product::edit(categories);
	std::cout << "4. Enter available kilograms: \n";
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
			std::cout << "Enter kilograms: ";
			unsigned kilograms = 0;
			std::cin >> kilograms;
			setQuantity(kilograms);
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

void ProductsByWeight::printFormatted() const
{
    std::cout << getProductName() << " : " << getPrice() << " : " << availableKilograms << std::endl;
}

void ProductsByWeight::print() const {
    printBasicInfo();
    std::cout << "\nAvailable kilograms: " << availableKilograms << " kg\n";
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
