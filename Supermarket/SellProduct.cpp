#include "SellProduct.h"

void SellProduct::sell(Supermarket& supermarket)
{
    if (supermarket.loggedData.type != UserType::Cashier) {
        throw std::runtime_error("Only a logged-in cashier can sell.");
    }

    double total = 0.0;
    unsigned transactionId = supermarket.transactions.size() + 1;
    unsigned productId = 0;
    MyVector<Pair<Product*, unsigned>> p;

    while (true) {
        supermarket.listProducts();

        std::cout << "Transaction ID: " << transactionId << '\n';
        std::cout << "Price: " << total << '\n';

        std::cout << "Enter product ID to sell. Enter END to end the transaction:\n";
        MyString input;
        std::cin >> input;

        if (input == "END") {
            break;
        }

        productId = strToUint(input);
        int productInd = supermarket.findProductById(productId);
        if (productInd == -1) {
            throw std::invalid_argument("Invalid product index");
        }

        std::cout << "Enter quantity:\n";
        unsigned quantity = 0;
        std::cin >> quantity;

        Product* base = supermarket.products[productInd].get();

        p.push_back({base, quantity});

        if (ProductsByUnit* byUnit = dynamic_cast<ProductsByUnit*>(base)) {
            unsigned availableQuantity = byUnit->getQuantity();
            if (availableQuantity < quantity) {
                std::cout << "Not enought quantity!";
                continue;
            }
            byUnit->setQuantity(availableQuantity - quantity);
            total += byUnit->getPrice() * quantity;

        }
        else if (ProductsByWeight* weightProd = dynamic_cast<ProductsByWeight*>(base)) {
            unsigned availableKilograms = weightProd->getQuantity();
            if (availableKilograms < quantity) {
                std::cout << "Not enought quantity!";
                continue;
            }
            weightProd->setQuantity(availableKilograms - quantity);
            total += weightProd->getPrice() * quantity;

        }
        else {
            std::cout << "Unknown product type.\n";
            continue;
        }

        std::cout << "-------------";
    }

    char ch;
    std::cout << "Add voucher (Y/N)? ";
    std::cin >> ch;
    if (ch == 'Y' || ch == 'y') {
        MyString code;
        std::cout << "Enter voucher: ";
        std::cin >> code;
        int discountInd = supermarket.findDiscountBySpecialCode(code);
        if (discountInd == -1) {
            throw std::invalid_argument("Invalid discount special code");
        }
        GiftCard* discount = supermarket.discounts[discountInd].get();
        double totalDiscount = 0.0;

        for (int i = 0; i < p.size(); ++i) {
            int quantity = p[i].getRhs();

            std::cout << "Product name: " << p[i].getLhs()->getProductName() << '\n';
            std::cout << "Product category ID: " << p[i].getLhs()->getCategory().getId() << '\n';
            std::cout << "Voucher category ID: ";
            discount->getCategories();
            if (discount->meetsDiscountCriteria(*p[i].getLhs())) {
                double discountPercent = discount->getPercentage();
                double productPrice = p[i].getLhs()->getPrice();
                double currPrice = productPrice * quantity;

                double discountAmount = currPrice * (discountPercent / 100.0);
                totalDiscount += discountAmount;
            }
        }
        total -= totalDiscount;
        total = std::round(total * 100) / 100.0;
        std::cout << supermarket.discounts[discountInd].get()->getPercentage() << "% applied! Transaction complete!\n";
    }

    char buff[1024];
    MyString receiptFile = "receipt_" + MyString(uintToStr(transactionId, buff)) + ".txt";
    Transaction t(supermarket.loggedData.logged->getId(), total, receiptFile);
    std::ofstream ofs(t.getReceiptFileName().c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open receipt file.");
    }
    ofs << "RECEIPT\n";
    ofs << "TRANSACTION_ID:" << t.getId() << '\n';
    ofs << "CASHIER_ID:" << t.getCashierId() << '\n';
    ofs << t.getDate() << '\n';
    ofs << "------------------------------\n";

    for (int i = 0; i < p.size(); ++i) {
        const Product* prod = p[i].getLhs();
        unsigned quantity = p[i].getRhs();
        double unitPrice = prod->getPrice();
        double totalPrice = unitPrice * quantity;

        ofs << prod->getProductName() << '\n';
        ofs << quantity << "*" << unitPrice << " - " << totalPrice << '\n';
        ofs << "###\n";
    }

    ofs << "TOTAL:" << t.getTotalAmount() << '\n';
    ofs.close();

    std::cout << "Receipt saved as: " << receiptFile << std::endl;
    std::cout << "Total: " << total << " lv.\n";
   
    supermarket.loggedData.loggedCashier->incrementTransactionCount();
    if (supermarket.loggedData.loggedCashier->getTransactionCount() % 3 == 0) {
        std::cout << "Bonus! You've completed 3 transactions.\n";
        supermarket.loggedData.loggedCashier->removeElementFromQueue();
    }
}
