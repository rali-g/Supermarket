#pragma once
#include "../Supermarket/Supermarket.h"
#include <iostream>
#include <stdexcept>

class Command
{
public:
	virtual void execute(Supermarket* market) const = 0;
	virtual Command* clone() const = 0;
	virtual ~Command() = default;
};
