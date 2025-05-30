#pragma once
#include "../Command.hpp"
#include "../../Supermarket/Supermarket.h"
#include <fstream>

class AddCategory : public Command
{
public:
	Command* clone() const override;
	void execute(Supermarket* market) const override;
};