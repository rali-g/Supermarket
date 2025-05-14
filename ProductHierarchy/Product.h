#pragma once
#include "../Helpers/MyString.h"
#include "../Components/Products/Category.hpp"

class Product
{
private:
	MyString productName = "Unknown";
	Category* category;
	double price = 0.0;
	double discount = 0.0;
protected:
	void printBasicInfo() const;
public:
	Product() = default; 

	Product(const MyString& name, const Category& category, double price, double discount);
	Product(MyString&& name, Category&& category, double price, double discount);

	const MyString& getProductName() const;
	const Category& getCategory() const;
	double getPrice() const;
	double getDiscount() const;

	void setProductName(const MyString& name);
	void setCategory(const Category& category);
	void setPrice(double price);
	void setDiscount(double discount);

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	virtual void print() const = 0;
	virtual Product* clone() const = 0;
	virtual ~Product() = default;
};

