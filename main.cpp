#include "../../UsersHierarchy/Employee.h"
#include "../../UsersHierarchy/Cashier.h"
#include "../../Helpers/MyVector.hpp"
#include "../../UsersHierarchy/Manager.h"
#include "../../Components/CodeGenerator.hpp"
#include "../../Components/Transaction.h"
#include "../../Supermarket/Supermarket.h"
#include "../../ProductsHierarchy/ProductsByUnit.h"
#include "../../ProductsHierarchy/ProductsByWeight.h"
#include "../../Components/Warning.h"
#include "../../../Supermarket/Supermarket/Supermarket.h"
#include "../../Supermarket/SellProduct.h"
#include "../../CommandsHierarchy/Command.hpp"
#include "../../CommandsHierarchy/CommandFactory.h"
#include "../../SupermarketLauncher/SupermarketLauncher.h"
#include <ctime>
#include <iostream>
using namespace std;

int main() {
    try {
        SupermarketLauncher::run();
        return 0;
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}