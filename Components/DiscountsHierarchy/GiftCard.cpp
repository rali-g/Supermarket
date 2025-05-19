#include "GiftCard.h"

void GiftCard::generateCode()
{
    CodeGenerator* generator = new CodeGenerator;
    specialCode = generator->generateCardCode(id);
    delete generator;
}

void GiftCard::printBasicInfo() const
{
    std::cout << "Id: " << id ;
    std::cout << "\nSpecial code: " << specialCode;
    std::cout << "\nDiscount percentage: " << percentage;
}

GiftCard::GiftCard()
{
    generateCode();

    id = counter;
    counter++;
}

GiftCard::GiftCard(double percentage)
{
    setPercentage(percentage);
    generateCode();

    id = counter;
    counter++;
}

GiftCard::GiftCard(const GiftCard& other)
{
    specialCode = other.specialCode;
    percentage = other.percentage;

    id = counter;
    counter++;
}

GiftCard& GiftCard::operator=(const GiftCard& other)
{
    if (this != &other) {
        specialCode = other.specialCode;
        percentage = other.percentage;

        id = counter;
        counter++;
    }
    return *this;
}

void GiftCard::setPercentage(double percentage)
{
    if (percentage < 0.0) {
        throw std::invalid_argument("Invalid discount percentage");
    }
    this->percentage = percentage;
}

double GiftCard::getPercentage() const
{
    return percentage;
}

unsigned GiftCard::getId() const
{
    return id;
}

bool GiftCard::isValidSpecialCode(const MyString& specialCode) const
{
    return this->specialCode == specialCode;
}

void GiftCard::writeToFile(std::ofstream& ofs) const
{
    writeStringToFile(ofs, specialCode);
    ofs.write((const char*)&percentage, sizeof(percentage));
    ofs.write((const char*)&id, sizeof(id));
}

void GiftCard::readFromFile(std::ifstream& ifs)
{
    specialCode = readStringFromFile(ifs);
    ifs.read((char*)&percentage, sizeof(percentage));
    ifs.read((char*)&id, sizeof(id));
}

void GiftCard::print() const
{
    std::cout << "Percentage: " << percentage;
    std::cout << "\nId: " << id;
}

unsigned GiftCard::counter = 0;