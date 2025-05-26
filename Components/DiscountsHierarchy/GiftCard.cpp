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
}

GiftCard::GiftCard(double percentage)
{
    setPercentage(percentage);
    generateCode();

    id = counter;
    counter++;

    writeCodeToFile();
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

const MyString& GiftCard::getSpecialCode() const
{
    return specialCode;
}

unsigned GiftCard::getId() const
{
    return id;
}

bool GiftCard::isValidSpecialCode(const MyString& specialCode) const
{
    return this->specialCode == specialCode;
}

void GiftCard::writeCodeToFile() const
{
    char buff[1024];
    MyString filename = MyString(uintToStr(getId(), buff)) + "_special_code.txt";

    std::ofstream ofs(filename.c_str(), std::ios::out | std::ios::trunc);

    if (!ofs.is_open()) {
        throw std::runtime_error("Can not open file!");
    }

    ofs << specialCode << std::endl;

    ofs.close();
}

const MyString& GiftCard::readCodeFromFile()
{
    char buff[1024];
    MyString filename = MyString(uintToStr(getId(), buff)) + "_special_code.txt";

    std::ifstream ifs(filename.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    char line[1024];
    ifs.getline(line, 1024);

    specialCode = MyString(line);

    ifs.close();
    return specialCode;
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