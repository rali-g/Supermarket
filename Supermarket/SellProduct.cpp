//#include "SellProduct.h"
//
//void SellProduct::sell(Supermarket& supermarket)
//{
//    if (supermarket.loggedData.type != UserType::Cashier) {
//        throw std::runtime_error("Only a logged-in cashier can sell.");
//    }
//
//    Transaction transaction;
//    double total = 0.0;
//    unsigned transactionId = supermarket.transactions.size() + 1;
//
//    while (true) {
//        supermarket.listProducts();
//
//        std::cout << "Transaction ID: " << transactionId << '\n';
//        std::cout << "Price: " << total << '\n';
//
//        std::cout << "Enter product ID to sell. Enter END to end the transaction:\n";
//        MyString input;
//        std::cin >> input;
//
//        if (input == "END") {
//            break;
//        }
//
//        unsigned productIndex = strToUint(input);
//        if (productIndex < 1 && productIndex > supermarket.products.size()) {
//            throw std::invalid_argument("Invalid product index");
//        }
//        productIndex--;
//
//        std::cout << "Enter quantity:\n";
//        unsigned quantity = 0.0;
//        std::cin >> quantity;
//
//        Product* base = supermarket.products[productIndex].get();
//        if (ProductsByUnit* byUnit= dynamic_cast<ProductsByUnit*>(base)) {
//            unsigned availableQuantity = byUnit->getAvailableQuantity();
//            if (availableQuantity < quantity) {
//                std::cout << "Not enought quantity!";
//                continue;
//            }
//            byUnit->setAvailableQuantity(availableQuantity - quantity);
//            total += byUnit->getPrice() * quantity;
//            PurchasedItem item;
//            item.product = supermarket.products[productIndex];
//            item.quantity = quantity;
//            currProducts.push_back(item);
//
//        }
//        else if (ProductsByWeight* weightProd = dynamic_cast<ProductsByWeight*>(base)) {
//            unsigned availableKilograms = weightProd->getAvailableKilograms();
//            if (availableKilograms < quantity) {
//                std::cout << "Not enought quantity!";
//                continue;
//            }
//            weightProd->setAvailableKilograms(availableKilograms - quantity);
//            total += weightProd->getPrice() * quantity;
//            PurchasedItem item;
//            item.product = supermarket.products[productIndex];
//            item.quantity = quantity;
//            currProducts.push_back(item);
//
//        }
//        else {
//            std::cout << "Unknown product type.\n";
//            continue;
//        }
//
//        std::cout << "-------------";
//    }
//
//    char ch;
//    std::cout << "Add voucher (Y/N)? ";
//    std::cin >> ch;
//    if (ch == 'Y' || ch == 'y') {
//        MyString code;
//        std::cout << "Enter voucher: ";
//        std::cin >> code;
//
//        
//    }
//
//    // Създай файл с касова бележка
//    MyString receiptFile = "receipt_" + uintToStr(transactionId) + ".txt";
//    transaction->finalize(loggedData.loggedCashier->getId(), total, receiptFile);
//    transaction->saveToFile(receiptFile);
//    transactions.push_back(*transaction);
//
//    // Ъпдейт на касиера
//    loggedData.loggedCashier->incrementTransactions();
//    if (loggedData.loggedCashier->getTransactionCount() % 3 == 0) {
//        loggedData.loggedCashier->forgiveOldestWarning();
//    }
//
//    std::cout << "Receipt saved as: " << receiptFile << '\n';
//    std::cout << "Total: " << total << " lv\n";
//}
