#include "Supermarket.h"
int Supermarket::findEmployeeById(unsigned id) const {
	for (int i = 0; i < employees.size(); ++i) {
		if (employees[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

bool Supermarket::employeeExists(const Employee& e) const
{
	for (int i = 0; i < employees.size(); ++i) {
		if (employees[i]->getId() == e.getId()) {
			return true;
		}
	}
	return false;
}

bool Supermarket::productExists(const Product& product) const
{
	for (int i = 0; i < employees.size(); ++i) {
		if (products[i]->getId() == product.getId()) {
			return true;
		}
	}
	return false;
}

bool Supermarket::discountExists(const GiftCard& card) const
{
	for (int i = 0; i < discounts.size(); ++i) {
		if (discounts[i]->getId() == card.getId()) {
			return true;
		}
	}
	return false;
}

bool Supermarket::transactionExists(const Transaction& t) const
{
	for (int i = 0; i < transactions.size(); ++i) {
		if (transactions[i].getId() == t.getId()) {
			return true;
		}
	}
	return false;
}

bool Supermarket::categoryExists(const Category& c) const
{
	for (int i = 0; i < categories.size(); ++i) {
		if (categories[i].getId() == c.getId()) {
			return true;
		}
	}
	return false;
}

int Supermarket::findProductById(unsigned id) const
{
	for (int i = 0; i < products.size(); i++) {
		if (products[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

static bool isLogInDataValid(unsigned id, const MyString& password, const Employee* employee)
{
	if (!employee)
	{
		return false;
	}

	return (employee->getId() == id && employee->isValidPassword(password));
}

void Supermarket::_register(const UserType& type, const MyString& firstName, const MyString& lastName, const MyString& phoneNumber, unsigned age, const MyString& password)
{
	switch (type) {
	case UserType::Cashier: {
		Cashier request(firstName, lastName, phoneNumber, password, age);
		pendingRequests.push_back(request);
		break;
	}
	case UserType::Manager:
		Manager manager(firstName, lastName, phoneNumber, password, age);
		employees.push_back(manager.clone());
		break;
	}
}

void Supermarket::_approveRegistration(unsigned id)
{
	if (loggedData.type == UserType::Manager) {
		for (int i = 0; i < pendingRequests.size(); i++) {
			if (pendingRequests[i].getId() == id) {
				employees.push_back(pendingRequests[i].clone());
				pendingRequests.erase(i);
				return;
			}
		}
	}
	throw std::exception("User is not manager! Permission denied!");
}

void Supermarket::_disapproveRegistration(unsigned id)
{
	if (loggedData.type == UserType::Manager) {
		for (int i = 0; i < pendingRequests.size(); i++) {
			if (pendingRequests[i].getId() == id) {
				pendingRequests.erase(i);
				return;
			}
		}
	}
	throw std::exception("User is not manager! Permission denied!");
}

void Supermarket::login(unsigned id, const MyString& password)
{
	if (loggedData.logged)
	{
		throw std::invalid_argument("Someone's logged in!");
	}

	for (size_t i = 0; i < employees.size(); i++)
	{
		if (isLogInDataValid(id, password, employees[i].get()))
		{
			loggedData.logged = employees[i].get();
			if (loggedData.loggedManager = dynamic_cast<Manager*>(employees[i].get()))
			{
				loggedData.type = UserType::Manager;
			}
			else if (loggedData.loggedCashier = dynamic_cast<Cashier*>(employees[i].get()))
			{
				loggedData.type = UserType::Cashier;
			}
			return;
		}
	}
	throw std::invalid_argument("Employee with these data details doesn't exist!");
}

void Supermarket::logout()
{
	loggedData = LoggedData();
}

void Supermarket::leave(unsigned id) {
	int index = findEmployeeById(id);
	if (index == -1) {
		throw std::invalid_argument("Invalid employee ID");
	}
	employees.erase(index);
}

const MyVector<polymorphic_ptr<Employee>>& Supermarket::getEmployees() const {
	return employees;
}

const MyVector<Transaction>& Supermarket::getTransactions() const {
	return transactions;
}

const MyVector<Category>& Supermarket::getCategories() const
{
	return categories;
}

const MyVector<polymorphic_ptr<Product>>& Supermarket::getProducts() const {
	return products;
}

const MyVector<polymorphic_ptr<GiftCard>>& Supermarket::getDiscounts() const {
	return discounts;
}

void Supermarket::addWarningToCashier(unsigned managerId, unsigned cashierId, const Warning& warning) {
	int managerIndex = findEmployeeById(managerId);
	int cashierIndex = findEmployeeById(cashierId);

	if (managerIndex == -1 && cashierIndex == -1) {
		throw std::invalid_argument("Invalid manager or cashier ID");
	}

	if (!dynamic_cast<Manager*>(employees[managerIndex].get())) {
		throw std::invalid_argument("Employee with managerId is not a manager");
	}

	Cashier* cashier = dynamic_cast<Cashier*>(employees[cashierIndex].get());
	if (!cashier) {
		throw std::invalid_argument("Employee with cashierId is not a cashier");
	}
	cashier->addElementToWarnings(warning);
	std::cout << "Warning added successfully.\n";
}

void Supermarket::listUserData() const
{
	if (!loggedData.logged)
	{
		throw std::invalid_argument("No user has logged in!");
	}
	loggedData.logged->whoAmI();
}

void Supermarket::listEmployees() const {
	std::cout << "Employees:\n";
	for (int i = 0; i < employees.size(); ++i) {
		employees[i]->print();
	}
}

void Supermarket::listProducts() const {
	std::cout << "Products:\n";
	for (int i = 0; i < products.size(); ++i) {
		products[i]->printFormatted();
	}
}

void Supermarket::listTransactions() const {
	std::cout << "Transactions:\n";
	for (int i = 0; i < transactions.size(); ++i) {
		transactions[i].print();
	}
}

void Supermarket::listGiftCards() const {
	std::cout << "Gift Cards:\n";
	for (int i = 0; i < discounts.size(); ++i) {
		discounts[i]->print();
	}
}

void Supermarket::listProductsByCategory(const Category& category) const
{
	const MyString& categoryName = category.getCategoryName();
	bool found = false;
	std::cout << "Products in category \"" << categoryName << "\":\n";

	for (size_t i = 0; i < products.size(); i++) {
		if (products[i]->getCategory().getCategoryName() == categoryName) {
			products[i]->printFormatted();
			found = true;
		}
	}

	if (!found) {
		std::cout << "No products found in this category.\n";
	}
}

void Supermarket::saveEmployees() const
{
	std::ofstream ofs("employees.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = employees.size();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		employees[i]->writeToFile(ofs);
	}

	ofs.close();
}

void Supermarket::saveProducts() const
{
	std::ofstream ofs("products.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = products.size();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		products[i]->writeToFile(ofs);
	}

	ofs.close();
}

void Supermarket::saveDiscounts() const
{
	std::ofstream ofs("discounts.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = discounts.size();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		discounts[i]->writeToFile(ofs);
	}

	ofs.close();
}

void Supermarket::saveCategories() const
{
	std::ofstream ofs("categories.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = categories.size();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		categories[i].writeToFile(ofs);
	}

	ofs.close();
}

void Supermarket::saveTransactions() const
{
	std::ofstream ofs("transactions.dat", std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = transactions.size();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		transactions[i].writeToFile(ofs);
	}

	ofs.close();
}

void Supermarket::loadEmployees()
{
	std::ifstream ifs("employees.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t size = 0;
	ifs.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		employees.push_back(UserFactory::createUser(ifs));
	}

	ifs.close();
}

void Supermarket::loadProducts()
{
	std::ifstream ifs("products.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t size = 0;
	ifs.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		products.push_back(ProductFactory::createProduct(ifs));
	}

	ifs.close();
}

void Supermarket::loadDiscounts()
{
	std::ifstream ifs("discounts.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t size = 0;
	ifs.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		discounts.push_back(GiftCardFactory::createGiftCard(ifs));
	}

	ifs.close();
}

void Supermarket::loadCategories()
{
	std::ifstream ifs("categories.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t size = 0;

	ifs.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		Category temp;
		temp.readFromFile(ifs);
		categories.push_back(std::move(temp));
	}

	ifs.close();
}

void Supermarket::loadTransactions()
{
	std::ifstream ifs("transactions.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	size_t size = 0;

	ifs.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		Transaction temp;
		temp.readFromFile(ifs);
		transactions.push_back(std::move(temp));
	}

	ifs.close();
}

void Supermarket::writeToFile() const
{
	saveEmployees();
	saveProducts();
	saveDiscounts();
	saveCategories();
	saveTransactions();
}

void Supermarket::readFromFile()
{
	loadEmployees();
	loadProducts();
	loadDiscounts();
	loadCategories();
	loadTransactions();
}

Supermarket::Supermarket()
{
	readFromFile();
}

Supermarket::~Supermarket()
{
	writeToFile();
}

void Supermarket::addCashier(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber, const MyString& password, unsigned age)
{
	Employee* client = new Cashier(firstName, secondName, phoneNumber, password, age);
	employees.push_back(client);
}

void Supermarket::addManager(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber, const MyString& password, unsigned age)
{
	Employee* manager = new Manager(firstName, secondName, phoneNumber, password, age);
	employees.push_back(manager);
}

void Supermarket::addTransaction(unsigned cashierId, int totalAmount, const MyString& date, const MyString& receiptFileName)
{
	Transaction tr(cashierId, totalAmount, date, receiptFileName);
	transactions.push_back(tr);
}

void Supermarket::addCategory(const MyString& categoryName, const MyString& description)
{
	Category c(categoryName, description);
	categories.push_back(c);
}

void Supermarket::addProductByUnit(const MyString& name, const Category& category, double price, double discount, unsigned availableQuantity)
{
	Product* productByUnit = new ProductsByUnit(name, category, price, discount, availableQuantity);
	products.push_back(productByUnit);
}

void Supermarket::addProductByWeight(const MyString& name, const Category& category, double price, double discount, double availableKilograms)
{
	Product* productByWeight = new ProductsByWeight(name, category, price, discount, availableKilograms);
	products.push_back(productByWeight);
}

void Supermarket::addSingleCategoryGiftCard(double percentage, unsigned categoryId)
{
	GiftCard* singleCard = new SingleCategoryGiftCard(percentage, categoryId);
	discounts.push_back(singleCard);
}

void Supermarket::addMultipleCategoryGiftCard(double percentage, const MyVector<unsigned>& categoryIds)
{
	GiftCard* multipleCard = new MultipleCategoryGiftCard(percentage, categoryIds);
	discounts.push_back(multipleCard);
}

void Supermarket::addAllProductsGiftCard()
{
	GiftCard* allCard = new AllProductsGiftCard();
	discounts.push_back(allCard);
}
