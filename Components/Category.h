#pragma once
#include "../../Helpers/MyString.h"
#include "../../Helpers/Helpers.h"

class Category {
private:
    MyString categoryName = "Unknown";
    MyString description = "Unknown";

    unsigned id = 0;
    static unsigned counter;
public:
    Category();
    Category(const MyString& categoryName, const MyString& description);
    Category(MyString&& categoryName, MyString&& description);
    Category(const Category& other);
    Category operator=(const Category& other);

    const MyString& getCategoryName() const;
    const MyString& getDescription() const;
    const unsigned getId() const;

    void setCategoryName(const MyString& categoryName);
    void setDescription(const MyString& description);

    void print() const;

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);
};
