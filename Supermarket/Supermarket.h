#include "../UsersHierarchy/Cashier.h"
#include "../UsersHierarchy/Manager.h"
#include "../ProductsHierarchy/Product.h"
#include "../Helpers/polymorphic_ptr.hpp"
#include "../Components/Transaction.h"
#include "../Components/DiscountsHierarchy/GiftCard.h"
#include "../UsersHierarchy/UserFactory.h"
#include "../ProductsHierarchy/ProductFactory.h"
#include "../Components/Category.hpp"
#include "../Components/DiscountsHierarchy/GiftCardFactory.h"

class Supermarket {
private:
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
	int findProductByName(const MyString& productName) const;

	~Supermarket();
public:
	Supermarket();

	Supermarket(const Supermarket& other) = delete;
	Supermarket& operator=(const Supermarket& other) = delete;
		 
	void addEmployee(Employee* employee);
	void addTransaction(const Transaction& transaction);
	void addProduct(Product* product);
	void addGiftCard(GiftCard* giftCard);
	void addCategories(const Category& category);

	void leave(unsigned id);

	const MyVector<polymorphic_ptr<Employee>>& getEmployees() const;
	const MyVector<Transaction>& getTransactions() const;
	const MyVector<Category>& getCategories() const;
	const MyVector<polymorphic_ptr<Product>>& getProducts() const;
	const MyVector<polymorphic_ptr<GiftCard>>& getDiscounts() const;

	void listEmployees() const;
	void listProducts() const;
	void listTransactions() const;
	void listGiftCards() const;
	void listProductsByCategory(const Category& category) const;

	void addWarningToCashier(unsigned managerId, unsigned cashierId, const Warning& warning);
};