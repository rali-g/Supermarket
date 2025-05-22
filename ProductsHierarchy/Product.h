#pragma once
#include "../Helpers/MyString.h"
#include "../Components/Category.h"

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

	unsigned id = 0;;
	static unsigned counter;
protected:
	void printBasicInfo() const;
public:
	Product(); 

	Product(const MyString& name, const Category& category, double price);
	Product(MyString&& name, Category&& category, double price);
	Product(const Product& other);
	Product& operator=(const Product& other);

	const MyString& getProductName() const;
	const Category& getCategory() const;
	double getPrice() const;
	unsigned getId() const;

	void setProductName(const MyString& name);
	void setCategory(const Category& category);
	void setPrice(double price);

	virtual void setQuantity(unsigned quantity) = 0;
	virtual unsigned getQuantity() const = 0;
	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;
	virtual void edit() = 0;

	virtual void printFormatted() const = 0;
	virtual void print() const = 0;
	virtual Product* clone() const = 0;
	virtual ~Product() = default;
};
