#include "UserFactory.h"

Employee* UserFactory::createUser(std::ifstream& ifs)
{
	UserType type = UserType::Unknown;
	ifs.read(reinterpret_cast<char*>(&type), sizeof(type));
	if (!ifs) {
		return nullptr;
	}

	Employee* ptr = nullptr;

    switch (type) {
    case UserType::Cashier:
        ptr = new Cashier();
        ptr->readFromFile(ifs);
        break;
    case UserType::Manager:
        ptr = new Manager();
        ptr->readFromFile(ifs);
        break;
    default:
        return nullptr;
    }
	return ptr;
}