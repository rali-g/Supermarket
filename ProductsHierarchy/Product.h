#pragma once
#include "../Helpers/MyString.h"
#include "../Components/Category.hpp"

enum class ProductType
{
	Unknown,
	ProductsByUnit,
	ProductsByWeight
};


class Product
{
private:
	MyString productName = "Unknown";
	Category* category;
	double price = 0.0;
	double discount = 0.0;

	unsigned id = 0;;
	static unsigned counter;
protected:
	void printBasicInfo() const;
public:
	Product(); 

	Product(const MyString& name, const Category& category, double price, double discount);
	Product(MyString&& name, Category&& category, double price, double discount);
	Product(const Product& other);
	Product& operator=(const Product& other);

	const MyString& getProductName() const;
	const Category& getCategory() const;
	double getPrice() const;
	double getDiscount() const;
	unsigned getId() const;

	void setProductName(const MyString& name);
	void setCategory(const Category& category);
	void setPrice(double price);
	void setDiscount(double discount);

	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;

	virtual void printFormatted() const = 0;
	virtual void print() const = 0;
	virtual Product* clone() const = 0;
	virtual ~Product() = default;
};
