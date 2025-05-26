#include "Transaction.h"
#include "../../Helpers/Helpers.h" 

unsigned Transaction::counter = 1;

Transaction::Transaction() {
    getFormattedDate();
}

Transaction::Transaction(unsigned cashierId, int totalAmount,  const MyString& receiptFileName)
    : cashierId(cashierId), totalAmount(totalAmount), receiptFileName(receiptFileName), id(counter++) {
    getFormattedDate();
}

Transaction::Transaction(unsigned cashierId, int totalAmount, MyString&& receiptFileName)
    : cashierId(cashierId), totalAmount(totalAmount), 
    receiptFileName(std::move(receiptFileName)), id(counter++) {
    getFormattedDate();
}

Transaction::Transaction(const Transaction& other) : cashierId(other.cashierId),
    totalAmount(other.totalAmount), date(other.date), receiptFileName(other.receiptFileName) {
    getFormattedDate();
    id = other.id;
}

Transaction& Transaction::operator=(const Transaction& other)
{
    if (this != &other) {
        cashierId = other.cashierId;
        totalAmount = other.totalAmount;
        date = other.date;
        receiptFileName = other.receiptFileName;
        
        getFormattedDate();
        id = other.id;
    }
    return *this;
}
void Transaction::getFormattedDate()
{
    std::time_t currentTime;
    std::tm localTime;

    time(&currentTime);
    localtime_s(&localTime, &currentTime);

    char timeStr[1024];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);

    this->date = MyString(timeStr);
}

unsigned Transaction::getCashierId() const {
    return cashierId;
}

double Transaction::getTotalAmount() const {
    return totalAmount;
}

const MyString& Transaction::getDate() const {
    return date;
}

const MyString& Transaction::getReceiptFileName() const {
    return receiptFileName;
}

unsigned Transaction::getId() const {
    return id;
}

void Transaction::setCashierId(unsigned id) {
    cashierId = id;
}

void Transaction::setTotalAmount(int amount) {
    if (amount < 0)
        throw std::invalid_argument("Total amount cannot be negative.");
    totalAmount = amount;
}

void Transaction::setDate(const MyString& date) {
    this->date = date;
}

void Transaction::setReceiptFileName(const MyString& file) {
    this->receiptFileName = file;
}

void Transaction::writeToFile(std::ofstream& ofs) const {
    ofs.write((const char*)&cashierId, sizeof(cashierId));
    ofs.write((const char*)&totalAmount, sizeof(totalAmount));
    writeStringToFile(ofs, date);
    writeStringToFile(ofs, receiptFileName);
    ofs.write((const char*)&id, sizeof(id));
}

void Transaction::readFromFile(std::ifstream& ifs) {
    ifs.read((char*)&cashierId, sizeof(cashierId));
    ifs.read((char*)&totalAmount, sizeof(totalAmount));
    date = readStringFromFile(ifs);
    receiptFileName = readStringFromFile(ifs);
    ifs.read((char*)&id, sizeof(id));
    if (id > counter)
        counter = id;
}

void Transaction::print() const {
    std::cout << "Transaction ID: " << id << '\n';
    std::cout << "Cashier ID: " << cashierId << '\n';
    std::cout << "Total Amount: " << totalAmount << '\n';
    std::cout << "Date: " << date << '\n';
    std::cout << "Receipt File: " << receiptFileName << '\n';
}
