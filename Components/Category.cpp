#include "Category.h"

unsigned Category::counter = 500;

Category::Category() {
    id = counter;
    counter++;
}

Category::Category(const MyString& categoryName, const MyString& description) {
    setCategoryName(categoryName);
    setDescription(description);
    id = counter;
    counter++;
}

Category::Category(MyString&& categoryName, MyString&& description) :
    categoryName(std::move(categoryName)), description(std::move(description)) {
    id = counter;
    counter++;
}

Category::Category(const Category& other) {
    categoryName = other.categoryName;
    description = other.description;

    id = counter;
    counter++;
}

Category Category::operator=(const Category& other) {
    if (this != &other) {
        categoryName = other.categoryName;
        description = other.description;

        id = counter;
        counter++;
    }
    return *this;
}

const MyString& Category::getCategoryName() const {
    return categoryName;
}

const MyString& Category::getDescription() const {
    return description;
}

const unsigned Category::getId() const {
    return id;
}

void Category::setCategoryName(const MyString& categoryName) {
    this->categoryName = categoryName;
}

void Category::setDescription(const MyString& description) {
    this->description = description;
}

void Category::print() const {
    std::cout << "Category: " << getCategoryName() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Id: " << getId() << std::endl;
}

void Category::writeToFile(std::ofstream& ofs) const {
    writeStringToFile(ofs, categoryName);
    writeStringToFile(ofs, description);
    ofs.write((const char*)&id, sizeof(id));
}

void Category::readFromFile(std::ifstream& ifs) {
    categoryName = readStringFromFile(ifs);
    description = readStringFromFile(ifs);
    ifs.read((char*)&id, sizeof(id));
}