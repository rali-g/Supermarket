#pragma once
#include "Employee.h"
#include "Cashier.h"
#include "Manager.h"

class UserFactory {
public:
	static Employee* createUser(std::ifstream& ifs);
};