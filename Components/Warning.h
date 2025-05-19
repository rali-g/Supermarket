#pragma once
#include "../../Helpers/MyString.h"
#include "../../Helpers/Helpers.h"

enum class Severity {
    Low = 100,
    Medium = 200,
    High = 300
};

class Warning {
private:
    MyString sender;
    MyString description;
    Severity severity = Severity::Low;

public:
    Warning() = default;
    Warning(const MyString& sender, const MyString& description, const Severity& severity);
    Warning(MyString&& sender, MyString&& description, Severity&& severity);

    const MyString& getSender() const;
    const MyString& getDescription() const;
    Severity getSeverity() const;

    void setSender(const MyString& sender);
    void setDescription(const MyString& description);
    void setSeverity(const Severity& severity);

    void writeToFile(std::ofstream& ofs) const;
    void readFromFile(std::ifstream& ifs);

    void print() const;
};
