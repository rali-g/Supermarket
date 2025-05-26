#pragma once
#include "../Supermarket/Supermarket.h"
#include "../Components/Transaction.h"
#include <iostream>
#include <fstream>
#include "../Helpers/Pair.hpp"

class Supermarket;

class SellProduct {
public:
	static void sell(Supermarket& supermarketð);
};