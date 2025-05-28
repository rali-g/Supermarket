#include "Help.h"

Command* Help::clone() const
{
	return new Help(*this);
}

void Help::execute(Supermarket* market) const
{
	try
	{
		market->help();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
}