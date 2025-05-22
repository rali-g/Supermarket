#include "../UsersHierarchy/Cashier.h"
#include "../UsersHierarchy/Manager.h"
#include "../ProductsHierarchy/Product.h"
#include "../Helpers/polymorphic_ptr.hpp"
#include "../Components/Transaction.h"
#include "../Components/DiscountsHierarchy/GiftCard.h"
#include "../UsersHierarchy/UserFactory.h"
#include "../ProductsHierarchy/ProductFactory.h"
#include "../Components/Category.h"
#include "../Components/DiscountsHierarchy/GiftCardFactory.h"
#include "../ProductsHierarchy/ProductsByUnit.h"
#include "../ProductsHierarchy/ProductsByWeight.h"
#include <iostream>
#include <sstream>
#include <fstream>

class Supermarket {
private:
	struct LoggedData
	{
		Employee* logged = nullptr;
		Cashier* loggedCashier = nullptr;
		Manager* loggedManager = nullptr;
		UserType type = UserType::Unknown;
	};


	LoggedData loggedData;
	MyVector<Cashier> pendingRequests;
	MyVector<Transaction> transactions;
	MyVector<Category> categories;
	MyVector<polymorphic_ptr<Employee>> employees;
	MyVector<polymorphic_ptr<Product>> products;
	MyVector<polymorphic_ptr<GiftCard>> discounts;

	void saveEmployees() const;
	void saveProducts() const;
	void saveDiscounts() const;
	void saveCategories() const;
	void saveTransactions() const;

	void loadEmployees();
	void loadProducts();
	void loadDiscounts();
	void loadCategories();
	void loadTransactions();

	void writeToFile() const;
	void readFromFile();

	int findEmployeeById(unsigned id) const;
	int findProductById(unsigned id) const;
	int findCategoryById(unsigned id) const;
	Category* findCategory(const MyString& name, const MyString& description);

	bool employeeExists(const Employee& e) const;
	bool productExists(const Product& product) const;
	bool discountExists(const GiftCard& card) const;
	bool transactionExists(const Transaction& t) const;
	bool categoryExists(const Category& c) const;

	Supermarket();
	~Supermarket();
public:
	Supermarket(const Supermarket& other) = delete;
	Supermarket& operator=(const Supermarket& other) = delete;
		 
	void addCashier(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber,
		const MyString& password, unsigned age);
	void addManager(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber,
		const MyString& password, unsigned age);
	void addTransaction(unsigned cashierId, int totalAmount, const MyString& date, const MyString& receiptFileName);
	void addProductByUnit(const MyString& name, const Category& category,
		double price, unsigned availableQuantity);
	void addProductByWeight(const MyString& name, const Category& category,
		double price, unsigned availableKilograms);
	void addSingleCategoryGiftCard(double percentage, unsigned categoryId);
	void addMultipleCategoryGiftCard(double percentage, const MyVector<unsigned>& categoryIds);
	void addAllProductsGiftCard();

	void _register(const UserType& type, const MyString& firstName, const MyString& lastName, 
		const MyString& phoneNumber, unsigned age, const MyString& password);
	void login(unsigned id, const MyString& password);
	void logout();
	void leave(unsigned id);

	const MyVector<polymorphic_ptr<Employee>>& getEmployees() const;
	const MyVector<Transaction>& getTransactions() const;
	const MyVector<Category>& getCategories() const;
	const MyVector<polymorphic_ptr<Product>>& getProducts() const;
	const MyVector<polymorphic_ptr<GiftCard>>& getDiscounts() const;

	//manager commands
	void listWarnedCahiers(unsigned points) const;
	void listPending() const;
	void warnCashier(unsigned cashierId, unsigned points, const MyString& description);
	void promoteCashier(unsigned cashierId, const MyString& specialCode);
	void _approveRegistration(unsigned id, const MyString& specialCode);
	void _disapproveRegistration(unsigned id, const MyString& specialCode);
	void fireCashier(unsigned cashierId, const MyString& specialCode);
	void addCategory(const MyString& name, const MyString& description);
	void editCategory(unsigned categoryId);
	void deleteCategory(unsigned categoryId);
	void addProduct(const ProductType& type);
	void editProduct(unsigned productId);
	void deleteProduct(unsigned productId);
	void _loadProducts(const MyString& fileName);
	void _loadGiftCards(const MyString& fileName);

	//cashier commands

	void listUserData() const;
	void listEmployees() const;
	void listProducts() const;
	void listTransactions() const;
	void listGiftCards() const;
	void listProductsByCategory(const Category& category) const;
};