#include "Warning.h"

Warning::Warning(const MyString& sender, const MyString& description, const Severity& severity) {
    setSender(sender);
    setDescription(description);
    setSeverity(severity);
}

const MyString& Warning::getSender() const {
    return sender;
}

const MyString& Warning::getDescription() const {
    return description;
}

Severity Warning::getSeverity() const {
    return severity;
}

void Warning::setSender(const MyString& sender) {
    if (sender.getSize() == 0)
        throw std::invalid_argument("Sender cannot be empty.");
    this->sender = sender;
}

void Warning::setDescription(const MyString& description) {
    if (description.getSize() == 0)
        throw std::invalid_argument("Description cannot be empty.");
    this->description = description;
}

void Warning::setSeverity(const Severity& severity) {
    switch (severity) {
    case Severity::Low:
    case Severity::Medium:
    case Severity::High:
        this->severity = severity;
        break;
    default:
        throw std::invalid_argument("Invalid severity value.");
    }
}

void Warning::writeToFile(std::ofstream& ofs) const
{
    writeStringToFile(ofs, sender);
    writeStringToFile(ofs, description);
    int severityToInt = static_cast<int>(severity);
    ofs.write(reinterpret_cast<const char*>(&severityToInt), sizeof(severityToInt));
}

void Warning::readFromFile(std::ifstream& ifs)
{
    sender = readStringFromFile(ifs);
    description = readStringFromFile(ifs);
    int severityInt;
    ifs.read(reinterpret_cast<char*>(&severityInt), sizeof(severityInt));
    severity = static_cast<Severity>(severityInt);
}

void Warning::print() const {
    std::cout << "Sender: " << sender << "\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Severity: ";
    switch (severity) {
    case Severity::Low: std::cout << "Low (100)\n"; break;
    case Severity::Medium: std::cout << "Medium (200)\n"; break;
    case Severity::High: std::cout << "High (300)\n"; break;
    default: std::cout << "Unknown\n"; break;
    }
}
