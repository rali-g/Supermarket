#include "UserFactory.h"

User* UserFactory::createUser(std::ifstream& ifs)
{
	UserType type;
	User* ptr = nullptr;
	ifs.read((char*)&type, sizeof(type));

	switch (type) {
		case UserType::Cashier
		ptr = new Cashier();
		ptr->readFromFile(ifs);
		break;
	case UserType::Manager:
		ptr = new Manager();
		ptr->readFromFile(ifs);
		break;
	}
	return ptr;
}