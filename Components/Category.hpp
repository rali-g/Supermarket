#include "../../Helpers/MyString.h"
#include "../../Helpers/Helpers.h"
#pragma once

class Category {
private:
	MyString categoryName = "Unknown";
	MyString description = "Unknown";

	unsigned id = 0;;
	static unsigned counter;
public:
	Category() {
		id = counter;
		counter++;
	}
	Category(const MyString& categoryName, const MyString& description) {
		setCategoryName(categoryName);
		setDescription(description);
		id = counter;
		counter++;
	}
	Category(MyString&& categoryName, MyString&& description) : 
		categoryName(std::move(categoryName)), description(std::move(description)) {
		id = counter;
		counter++;
	}

	Category(const Category& other) {
		categoryName = other.categoryName;
		description = other.description;

		id = counter;
		counter++;
	}

	Category operator=(const Category& other) {
		if (this != &other) {
			categoryName = other.categoryName;
			description = other.description;

			id = counter;
			counter++;
		}
		return *this;
	}

	const MyString& getCategoryName() const { 
		return categoryName; 
	}
	const MyString& getDescription() const { 
		return description; 
	}
	const unsigned getId() const {
		return id;
	}

	void setCategoryName(const MyString& categoryName) { 
		this->categoryName = categoryName; 
	}

	void setDescription(const MyString& descroption) {
		this->description = descroption;
	}

	void print() const {
		std::cout << "Category: " << getCategoryName() << std::endl;
		std::cout << "Description: " << getDescription() << std::endl;
		std::cout << "Id: " << getId() << std::endl;
	}

	void writeToFile(std::ofstream& ofs) const {
		writeStringToFile(ofs, categoryName);
		writeStringToFile(ofs, description);
		ofs.write((const char*)&id, sizeof(id));
	}
	void readFromFile(std::ifstream& ifs) {
		categoryName = readStringFromFile(ifs);
		description = readStringFromFile(ifs);
		ifs.read((char*)&id, sizeof(id));
	}

};

unsigned Category::counter = 500;