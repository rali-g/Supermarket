#include "../../SupermarketLauncher/SupermarketLauncher.h"
#include <iostream>

int main() {
    try {
        SupermarketLauncher::run();
        return 0;
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}
