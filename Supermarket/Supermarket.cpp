#define _CRT_SECURE_NO_WARNINGS
#include "Supermarket.h"


int Supermarket::findEmployeeById(unsigned id) const {
	for (int i = 0; i < employees.size(); ++i) {
		if (employees[i]->getId() == id) {
			return i;
		}
	}
	return -1;
}

Category* Supermarket::findCategoryByName(const MyString& name) {
	for (size_t i = 0; i < categories.size(); i++) {
		if (categories[i].getCategoryName() == name) {
			return &categories[i];
		}
	}
	return nullptr;
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
	for (int i = 0; i < products.size(); ++i) {
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
		if (categories[i].getCategoryName() == c.getCategoryName()) {
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

int Supermarket::findCategoryById(unsigned id) const
{
	for (int i = 0; i < categories.size(); i++) {
		if (categories[i].getId() == id) {
			return i;
		}
	}
	return -1;
}

int Supermarket::findDiscountBySpecialCode(const MyString& code) const
{
	for (int i = 0; i < discounts.size(); i++) {
		if (discounts[i].get()->isValidSpecialCode(code)) {
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

void Supermarket::approveRegistration(unsigned id, const MyString& specialCode)
{
	if (loggedData.type == UserType::Manager && loggedData.loggedManager->readCodeFromFile() == specialCode) {
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

void Supermarket::disapproveRegistration(unsigned id, const MyString& specialCode)
{
	if (loggedData.type == UserType::Manager && loggedData.loggedManager->readCodeFromFile() == specialCode) {
		for (int i = 0; i < pendingRequests.size(); i++) {
			if (pendingRequests[i].getId() == id) {
				pendingRequests.erase(i);
				return;
			}
		}
	}
	throw std::exception("User is not manager! Permission denied!\n");
}

void Supermarket::login(unsigned id, const MyString& password)
{
	if (loggedData.logged)
	{
		throw std::invalid_argument("Someone's logged in!\n");
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
			std::cout << "You successfully logged in!\n";
			return;
		}
	}
	throw std::invalid_argument("Permission denied!\n");
}

void Supermarket::logout()
{
	loggedData = LoggedData();
	std::cout << "You successfully logged out!\n";
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

void Supermarket::listWarnedCahiers(unsigned points) const
{
	for (int i = 0; i < employees.size(); i++)
	{
		const Cashier* cashier = dynamic_cast<const Cashier*>(employees[i].get());
		if (cashier && cashier->getWarningPoints() > points)
		{
			cashier->print(); 
			std::cout << std::endl;
		}
	}
}

void Supermarket::listPending() const
{
	int ind = 0;
	for (int i = 0; i < pendingRequests.size(); i++) {
		pendingRequests[i].print();
	}
}

void Supermarket::warnCashier(unsigned cashierId, unsigned points, const MyString& description)
{
	int ind = 0;
	if (loggedData.type == UserType::Manager) {
		ind = findEmployeeById(cashierId);
		if (ind == -1) {
			throw std::invalid_argument("Invalid cashier Id");
		}
		Cashier* cashier = dynamic_cast<Cashier*>(employees[ind].get());
		if (!cashier) {
			throw std::invalid_argument("Employee is not a cashier");
		}
		Severity severity;
		if (points == 100) {
			severity = Severity::Low;
		}
		else if (points == 200) {
			severity = Severity::Medium;
		}
		else if (points == 300) {
			severity = Severity::High;
		}
		else {
			throw std::invalid_argument("Invalid severity points!");
		}
		Warning warning(loggedData.loggedManager->getFirstName(), description, severity);
		cashier->addElementToWarnings(warning);
		return;
	}

	throw std::invalid_argument("Permission denied");
}

void Supermarket::promoteCashier(unsigned cashierId, const MyString& specialCode)
{
	if (loggedData.type != UserType::Manager || loggedData.loggedManager->readCodeFromFile() != specialCode)
		throw std::invalid_argument("Permission denied or invalid code.");

	int index = findEmployeeById(cashierId);
	if (index == -1)
		throw std::invalid_argument("Cashier not found.");

	Cashier* cashier = dynamic_cast<Cashier*>(employees[index].get());
	if (!cashier)
		throw std::invalid_argument("Employee is not a cashier.");

	Manager* newManager = new Manager(cashier->getFirstName(), cashier->getSecondName(), 
		cashier->getPhoneNumber(), cashier->getPassword(), cashier->getAge());
	employees[index].reset(newManager);
}

void Supermarket::sell()
{
	SellProduct::sell(*this);
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
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i]) {
			employees[i]->print();
			std::cout << std::endl;
		}
	}
}

void Supermarket::listCategories() const
{
	std::cout << "Categories:\n";
	for (int i = 0; i < categories.size(); ++i) {
		categories[i].print();
	}
}

void Supermarket::listProducts() const {
	std::cout << "\nProducts:\n";
	for (int i = 0; i < products.size(); ++i) {
		std::cout << products[i].get()->getId() << ". ";
		if (products[i]) {
			products[i]->printFormatted();
		}
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
		if (discounts[i]) {
			discounts[i]->print();
			std::cout << std::endl << discounts[i].get()->getSpecialCode();
			std::cout << "\n\n";
		}
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

//Supermarket::~Supermarket()
//{
//	writeToFile();
//}

Supermarket& Supermarket::getInstance()
{
	static Supermarket instance;
	return instance;
}

void Supermarket::addCashier(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber, const MyString& password, unsigned age)
{
	employees.push_back(polymorphic_ptr<Employee>(new Cashier(firstName, secondName, phoneNumber, password, age)));
}

void Supermarket::addManager(const MyString& firstName, const MyString& secondName, const MyString& phoneNumber, const MyString& password, unsigned age)
{
	employees.push_back(polymorphic_ptr<Employee>(new Manager(firstName, secondName, phoneNumber, password, age)));
}

void Supermarket::addTransaction(unsigned cashierId, int totalAmount, const MyString& receiptFileName)
{
	Transaction tr(cashierId, totalAmount, receiptFileName);
	transactions.push_back(tr);
}

void Supermarket::fireCashier(unsigned cashierId, const MyString& specialCode)
{
	int ind = 0;
	if (loggedData.type == UserType::Manager && loggedData.loggedManager->readCodeFromFile() == specialCode) {
		ind = findEmployeeById(cashierId);
		if (ind == -1) {
			throw std::invalid_argument("Invalid cashier ID");
		}
		employees.erase(ind);
		return;
	}
	throw std::invalid_argument("\nPermission denied!");
}

void Supermarket::addCategory(const MyString& categoryName, const MyString& description)
{
	if (loggedData.logged && loggedData.type == UserType::Manager) {
		Category c(categoryName, description);
		categories.push_back(c);
		return;
	}
	throw std::invalid_argument("\nPermission denied!");
}

void Supermarket::editCategory(unsigned categoryId)
{
	if (loggedData.type != UserType::Manager) {
		throw std::invalid_argument("\nPermission denied!");
	}
	int ind = findCategoryById(categoryId);
	if (ind == -1) {
		throw std::invalid_argument("Invalid category id!");
	}
	categories[ind].editCategory();
}

void Supermarket::deleteCategory(unsigned categoryId)
{
	if (loggedData.type != UserType::Manager) {
		throw std::invalid_argument("\nPermission denied!");
	}
	int ind = findCategoryById(categoryId);
	if (ind == -1) {
		throw std::invalid_argument("\nInvalid category id!");
	}
	for (int i = 0; i < products.size(); i++) {
		if (products[i].get()->getCategory().getId() == categoryId) {
			return;
		}

	}
	categories.erase(ind);
}

void Supermarket::addProductByUnit(const MyString& name, const Category& category, double price, unsigned availableQuantity)
{
	products.push_back(new ProductsByUnit(name, category, price, availableQuantity));
}

void Supermarket::addProductByWeight(const MyString& name, const Category& category, double price, unsigned availableKilograms)
{
	products.push_back(new ProductsByWeight(name, category, price, availableKilograms));
}

void Supermarket::addSingleCategoryGiftCard(double percentage, unsigned categoryId)
{
	discounts.push_back(new SingleCategoryGiftCard(percentage, categoryId));
}

void Supermarket::addMultipleCategoryGiftCard(double percentage, const MyVector<unsigned>& categoryIds)
{
	discounts.push_back(new MultipleCategoryGiftCard(percentage, categoryIds));
}

void Supermarket::addAllProductsGiftCard(double percent)
{
	discounts.push_back(new AllProductsGiftCard(percent));
}

void Supermarket::addProduct(const ProductType& type)
{
	if (loggedData.type != UserType::Manager) {
		throw std::invalid_argument("\nPermission denied!");
	}
	switch (type) {
	case ProductType::ProductsByUnit: {
		ProductsByUnit p;
		products.push_back(p.clone());
		break;
	}
	case ProductType::ProductsByWeight:
		ProductsByWeight p;
		products.push_back(p.clone());
		break;
	}
}

void Supermarket::editProduct(unsigned productId)
{
	if (loggedData.type != UserType::Manager) {
		throw std::invalid_argument("\nPermission denied!");
	}
	int ind = findProductById(productId);
	if (ind == -1) {
		throw std::invalid_argument("Invalid product Id");
	}
	products[ind].get()->edit(categories);
	if (!categoryExists(products[ind].get()->getCategory())){
		categories.push_back(products[ind].get()->getCategory());
	}
}

void Supermarket::deleteProduct(unsigned productId)
{
	int ind = findProductById(productId);
	if (ind == -1) {
		throw std::invalid_argument("Invalid product Id");
	}
	products.erase(ind);
}

void Supermarket::loadProducts(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open()) return;

	char buffer[1024];
	while (ifs.getline(buffer, sizeof(buffer))) {
		char* token = std::strtok(buffer, ":");
		if (!token) continue;

		if (std::strcmp(token, "NEW") == 0) {
			char* productTypeStr = std::strtok(nullptr, ":");
			if (!productTypeStr) continue;

			char* nameStr = std::strtok(nullptr, ":");
			char* categoryNameStr = std::strtok(nullptr, ":");
			char* categoryDescStr = std::strtok(nullptr, ":");
			char* priceStr = std::strtok(nullptr, ":");
			char* quantityStr = std::strtok(nullptr, ":");

			if (!nameStr || !categoryNameStr || !priceStr || !quantityStr) continue;

			MyString name(nameStr);
			MyString categoryName(categoryNameStr);
			double price = strtod(priceStr, nullptr);

			Category* category = findCategoryByName(categoryName);
			if (!category) {
				throw std::invalid_argument("Category not found while loading product.");
			}

			if (std::strcmp(productTypeStr, "ProductsByUnit") == 0) {
				unsigned availableQuantity = static_cast<unsigned>(strtoul(quantityStr, nullptr, 10));
				auto* product = new ProductsByUnit(name, *category, price, availableQuantity);
				products.push_back(polymorphic_ptr<Product>(product));
			}
			else if (std::strcmp(productTypeStr, "ProductsByWeight") == 0) {
				double availableKg = strtod(quantityStr, nullptr);
				auto* product = new ProductsByWeight(name, *category, price, availableKg);
				products.push_back(polymorphic_ptr<Product>(product));
			}
		}
		else {
			char* productTypeStr = token;
			char* productIdStr = std::strtok(nullptr, ":");
			char* quantityStr = std::strtok(nullptr, ":");

			if (!productTypeStr || !productIdStr || !quantityStr) continue;

			unsigned productId = static_cast<unsigned>(std::strtoul(productIdStr, nullptr, 10));
			double quantity = std::strtod(quantityStr, nullptr);

			int idx = findProductById(productId);
			if (idx == -1) {
				throw std::invalid_argument("Product is not in storage. Could not load new quantity.");
			}

			Product* prod = products[idx].get();
			prod->setQuantity(prod->getQuantity() + quantity);
		}
	}
}

void Supermarket::loadGiftCards(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open()) {
		throw std::runtime_error("Cannot open file");
	}

	const size_t MAX_LINE_LEN = 512;
	char line[MAX_LINE_LEN];

	while (ifs.getline(line, MAX_LINE_LEN)) {
		if (line[0] == '\0') continue;

		char* token = std::strtok(line, ":");
		if (!token) continue;

		if (std::strcmp(token, "SingleCategoryCard") == 0) {
			char* categoryStr = std::strtok(nullptr, ":");
			char* percentStr = std::strtok(nullptr, ":");

			if (!categoryStr || !percentStr) {
				throw std::invalid_argument("Invalid SingleCategoryGiftCard format");
				continue;
			}

			unsigned category = static_cast<unsigned>(std::strtoul(categoryStr, nullptr, 10));
			double percent = std::strtod(percentStr, nullptr);

			discounts.push_back(polymorphic_ptr<GiftCard>(new SingleCategoryGiftCard(percent, category)));

		}
		else if (std::strcmp(token, "MultipleCategoryCard") == 0) {
			char* countStr = std::strtok(nullptr, ":");
			if (!countStr) {
				throw std::invalid_argument("Missing count for MultipleCategoryCard");
				continue;
			}

			unsigned count = static_cast<unsigned>(std::strtoul(countStr, nullptr, 10));
			MyVector<unsigned> categories;

			for (unsigned i = 0; i < count; i++) {
				char* catStr = std::strtok(nullptr, ":");
				if (!catStr) {
					throw std::invalid_argument("Not enough categories provided for MultipleCategoryCard");
					break;
				}
				unsigned cat = static_cast<unsigned>(std::strtoul(catStr, nullptr, 10));
				categories.push_back(cat);
			}

			char* percentStr = std::strtok(nullptr, ":");
			if (!percentStr) {
				throw std::invalid_argument("Missing percentage for MultipleCategoryCard");
				continue;
			}

			double percent = std::strtod(percentStr, nullptr);
			discounts.push_back(polymorphic_ptr<GiftCard>(new MultipleCategoryGiftCard(percent, categories)));

		}
		else if (std::strcmp(token, "AllProductsCard") == 0) {
			char* percentStr = std::strtok(nullptr, ":");
			if (!percentStr) {
				throw std::invalid_argument("Missing percentage for AllProductsCard");
				continue;
			}

			double percent = std::strtod(percentStr, nullptr);
			discounts.push_back(polymorphic_ptr<GiftCard>(new AllProductsGiftCard(percent)));

		}
		else {
			throw std::invalid_argument("Unknown gift card type");
		}
	}
}

