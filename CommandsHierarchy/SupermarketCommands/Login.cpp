#include "Login.h"

Command* Login::clone() const
{
	return new Login(*this);
}

void Login::execute(Supermarket* market) const
{
	unsigned int id = 0;
	MyString passwd;
	std::cin >> id >> passwd;
	try
	{
		market->login(id, passwd);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}