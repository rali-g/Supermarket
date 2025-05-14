#pragma once
#include "../../Helpers/MyVector.hpp"
#include "Transaction.h"

class TransactionInfo
{
private:
	MyVector<Transaction> transactions;
public:
    TransactionInfo() = default;

    void addTransaction(const Transaction& transaction);
    void addTransaction(Transaction&& transaction);

    void addTransactionAtIndex(size_t index, const Transaction& transaction);
    void addTransactionAtIndex(size_t index, Transaction&& transaction);

    const Transaction& getByIndex(size_t index) const;

    void removeTransactionAtIndex(size_t index);

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);

    void print() const;
};

