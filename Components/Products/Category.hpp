#include "../../Helpers/MyString.h"
#include "../../Helpers/Helpers.h"

class Category {
private:
	MyString categoryName = "Unknown";
	MyString description = "Unknown";
public:
	Category() = default;
	Category(const MyString& categoryName, const MyString& description) {
		setCategoryName(categoryName);
		setDescription(description);
	}

	const MyString& getCategoryName() const { return categoryName; }
	const MyString& getDescription() const { return description; }

	void setCategoryName(const MyString& categoryName) { 
		this->categoryName = categoryName; 
	}

	void setDescription(const MyString& descroption) {
		this->description = descroption;
	}

	void print() const {
		std::cout << "Category: " << getCategoryName() << std::endl;
		std::cout << "Description: " << getDescription() << std::endl;
	}

	void writeToFile(std::ofstream& ofs) const {
		writeStringToFile(ofs, categoryName);
		writeStringToFile(ofs, description);
	}
	void readFromFile(std::ifstream& ifs) {
		categoryName = readStringFromFile(ifs);
		description = readStringFromFile(ifs);
	}

};