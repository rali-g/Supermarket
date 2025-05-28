#include "SupermarketLauncher.h"
#include "../Supermarket/Supermarket.h"
#include "../CommandsHierarchy/CommandFactory.h"


void SupermarketLauncher::run()
{
	Supermarket& market = Supermarket::getInstance();
	MyString cmd = "";

	while (true)
	{
		std::cout << ">> ";
		std::cin >> cmd;

		if (cmd == "stop")
		{
			break;
		}

		polymorphic_ptr<Command> command = CommandFactory::createCommand(cmd);

		if (!command.get())
		{
			std::cout << "Invalid command!" << std::endl;
		}
		else
		{
			command->execute(&market);
		}

		std::cout << std::endl << std::endl;
	}
}