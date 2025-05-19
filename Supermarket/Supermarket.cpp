#include "Supermarket.h"

void Supermarket::addEmployee(Employee* employee)
{
	employees.push_back(polymorphic_ptr<Employee>(employee->clone()));
}

void Supermarket::addTransaction(const Transaction& transaction) {
	transactions.push_back(transaction);
}

void Supermarket::addProduct(Product* product) {
	products.push_back(polymorphic_ptr<Product>(product->clone()));
}

void Supermarket::addGiftCard(GiftCard* giftCard) {
	discounts.push_back(polymorphic_ptr<GiftCard>(giftCard->clone()));
}

void Supermarket::addCategories(const Category& category)
{
	categories.push_back(category);
}

int Supermarket::findEmployeeById(unsigned id) const {
	for (int i = 0; i < employees.size(); ++i) {
		if (employees[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

int Supermarket::findProductByName(const MyString& productName) const
{
	for (int i = 0; i < products.size(); i++) {
		if (products[i]->getProductName() == productName) {
			return i;
		}
	}
	return -1;
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
