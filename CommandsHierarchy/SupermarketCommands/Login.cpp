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
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for id. Login aborted.\n";
		return;
	}
	try
	{
		market->login(id, passwd);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}