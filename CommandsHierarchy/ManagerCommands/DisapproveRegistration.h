#pragma once
#include "../Command.hpp"
#include "../../Supermarket/Supermarket.h"

class DisapproveRegistration : public Command
{
public:
	Command* clone() const override;
	void execute(Supermarket* market) const override;
};