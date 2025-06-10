#pragma once
#include "../../Helpers/MyString.h"
#include "../../Components/CodeGenerator.hpp"
#include "../../ProductsHierarchy/Product.h"

enum class GiftCardType
{
	Unknown,
	SingleCategoryGiftCard,
	MultipleCategoryGiftCard,
	AllProductsGiftCard
};

class GiftCard
{
private:
	MyString specialCode = "Unknown";
	double percentage = 0.0;

	unsigned id = 0;;
	static unsigned counter;

	void generateCode();
protected:
	void printBasicInfo() const;
public:
	GiftCard();
	GiftCard(double percentage);
	GiftCard(const GiftCard& other);
	GiftCard& operator=(const GiftCard& other);
	virtual ~GiftCard() = default;

	void setPercentage(double percentage);
	double getPercentage() const;
	const MyString& getSpecialCode() const;
	unsigned getId() const;

	bool isValidSpecialCode(const MyString& specialCode) const;
	virtual bool meetsDiscountCriteria(const Product& product) const = 0;
	virtual void getCategories() const = 0;

	void writeCodeToFile() const;
	const MyString& readCodeFromFile();
	virtual void writeToFile(std::ofstream& ofs) const = 0;
	virtual void readFromFile(std::ifstream& ifs) = 0;

	virtual GiftCardType getGiftCardType() const = 0;
	virtual GiftCard* clone() const = 0;
	virtual void print() const = 0;
	virtual void whoAmI() const = 0;
};

