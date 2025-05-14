#include "TransactionInfo.h"
#include <fstream>

void TransactionInfo::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

void TransactionInfo::addTransaction(Transaction&& transaction) {
    transactions.push_back(std::move(transaction));  
}

void TransactionInfo::addTransactionAtIndex(size_t index, const Transaction& transaction) {
    if (index <= transactions.size()) {
        transactions.insert(transaction, index); 
    }
    else {
        throw std::out_of_range("Invalid index for adding transaction.");
    }
}

void TransactionInfo::addTransactionAtIndex(size_t index, Transaction&& transaction) {
    if (index <= transactions.size()) {
        transactions.insert(std::move(transaction), index);
    }
    else {
        throw std::out_of_range("Invalid index for adding transaction.");
    }
}

const Transaction& TransactionInfo::getByIndex(size_t index) const
{
    if (index <= transactions.size()) {
        return transactions[index];
    }
    else {
        throw std::out_of_range("Invalid index for adding transaction.");
    }
}

void TransactionInfo::removeTransactionAtIndex(size_t index) {
    if (index < transactions.size()) {
        transactions.erase(index);
    }
    else {
        throw std::out_of_range("Invalid index for adding transaction.");
    }
}

void TransactionInfo::writeToFile(std::ofstream& ofs) const {
    size_t transactionCount = transactions.size();
    ofs.write((const char*)&transactionCount, sizeof(unsigned));

    for (int i = 0; i < transactionCount; i++) {
        transactions[i].writeToFile(ofs);
    }
}

void TransactionInfo::readFromFile(std::ifstream& ifs) {
    size_t transactionCount = 0;
    ifs.read((char*)&transactionCount, sizeof(unsigned));

    for (size_t i = 0; i < transactionCount; ++i) {
        Transaction transaction;
        transaction.readFromFile(ifs);
        transactions.push_back(std::move(transaction));
    }
}

void TransactionInfo::print() const {
    size_t transactionCount = transactions.size();
    for (int i = 0; i < transactionCount; i++) {
        transactions[i].print();
    }
}
