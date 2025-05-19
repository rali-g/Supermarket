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
	void addCategory(const MyString& categoryName, const MyString& description);
	void addProductByUnit(const MyString& name, const Category& category,
		double price, double discount, unsigned availableQuantity);
	void addProductByWeight(const MyString& name, const Category& category,
		double price, double discount, double availableKilograms);
	void addSingleCategoryGiftCard(double percentage, unsigned categoryId);
	void addMultipleCategoryGiftCard(double percentage, const MyVector<unsigned>& categoryIds);
	void addAllProductsGiftCard();

	void _register(const UserType& type, const MyString& firstName, const MyString& lastName, 
		const MyString& phoneNumber, unsigned age, const MyString& password);
	void _approveRegistration(unsigned id);
	void _disapproveRegistration(unsigned id);
	void login(unsigned id, const MyString& password);
	void logout();
	void leave(unsigned id);

	const MyVector<polymorphic_ptr<Employee>>& getEmployees() const;
	const MyVector<Transaction>& getTransactions() const;
	const MyVector<Category>& getCategories() const;
	const MyVector<polymorphic_ptr<Product>>& getProducts() const;
	const MyVector<polymorphic_ptr<GiftCard>>& getDiscounts() const;

	void listUserData() const;
	void listEmployees() const;
	void listProducts() const;
	void listTransactions() const;
	void listGiftCards() const;
	void listProductsByCategory(const Category& category) const;

	void addWarningToCashier(unsigned managerId, unsigned cashierId, const Warning& warning);
};