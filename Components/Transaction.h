#pragma once
#include "../../Helpers/MyString.h"
#include <ctime>

class Transaction
{
private:
	unsigned cashierId = 0;
	double totalAmount = 0;
	MyString date = "Unknown";
	MyString receiptFileName = "Unknown";

	unsigned id = 0;
	static unsigned counter;

    void getFormattedDate();
public:
    Transaction();
    Transaction(unsigned cashierId, int totalAmount, const MyString& receiptFileName);
    Transaction(unsigned cashierId, int totalAmount, MyString&& receiptFileName);
    Transaction(const Transaction& other);
    Transaction& operator=(const Transaction& other);

    unsigned getCashierId() const;
    double getTotalAmount() const;
    const MyString& getDate() const;
    const MyString& getReceiptFileName() const;
    unsigned getId() const;

    void setCashierId(unsigned id);
    void setTotalAmount(int amount);
    void setDate(const MyString& date);
    void setReceiptFileName(const MyString& file);

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);

    void print() const;
};

