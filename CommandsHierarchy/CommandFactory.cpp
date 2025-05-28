#include "CommandFactory.h"
#include "../CommandsHierarchy/CashierCommands/Sell.h"
#include "../CommandsHierarchy/ManagerCommands/AddCategory.h"
#include "../CommandsHierarchy/ManagerCommands/AddProduct.h"
#include "../CommandsHierarchy/ManagerCommands/ApproveRegistration.h"
#include "../CommandsHierarchy/ManagerCommands/DeleteCategory.h"
#include "../CommandsHierarchy/ManagerCommands/DeleteProduct.h"
#include "../CommandsHierarchy/ManagerCommands/DisapproveRegistration.h"
#include "../CommandsHierarchy/ManagerCommands/EditCategory.h"
#include "../CommandsHierarchy/ManagerCommands/EditProduct.h"
#include "../CommandsHierarchy/ManagerCommands/FireCashier.h"
#include "../CommandsHierarchy/ManagerCommands/ListPending.h"
#include "../CommandsHierarchy/ManagerCommands/ListWarnedCashiers.h"
#include "../CommandsHierarchy/ManagerCommands/LoadGiftCards.h"
#include "../CommandsHierarchy/ManagerCommands/LoadProducts.h"
#include "../CommandsHierarchy/ManagerCommands/PromoteCashier.h"
#include "../CommandsHierarchy/ManagerCommands/WarnCashier.h"
#include "../CommandsHierarchy/SupermarketCommands/Leave.h"
#include "../CommandsHierarchy/SupermarketCommands/ListCategories.h"
#include "../CommandsHierarchy/SupermarketCommands/ListEmployees.h"
#include "../CommandsHierarchy/SupermarketCommands/ListGiftCards.h"
#include "../CommandsHierarchy/SupermarketCommands/ListProducts.h"
#include "../CommandsHierarchy/SupermarketCommands/ListProductsByCategory.h"
#include "../CommandsHierarchy/SupermarketCommands/ListTransactions.h"
#include "../CommandsHierarchy/SupermarketCommands/ListUserData.h"
#include "../CommandsHierarchy/SupermarketCommands/Login.h"
#include "../CommandsHierarchy/SupermarketCommands/Logout.h"
#include "../CommandsHierarchy/SupermarketCommands/Register.h"
#include "../CommandsHierarchy/SupermarketCommands/Help.h"

polymorphic_ptr<Command> CommandFactory::createCommand(const MyString& command)
{
	if (command == "sell")
	{
		return new Sell();
	}
	else if (command == "add_category")
	{
		return new AddCategory();
	}
	else if (command == "add_product")
	{
		return new AddProduct();
	}
	else if (command == "approve_registration")
	{
		return new ApproveRegistration();
	}
	else if (command == "delete_category")
	{
		return new DeleteCategory();
	}
	else if (command == "delete_product")
	{
		return new DeleteProduct();
	}
	else if (command == "disapprove_registration")
	{
		return new DisapproveRegistration();
	}
	else if (command == "edit_category")
	{
		return new EditCategory();
	}
	else if (command == "edit_product")
	{
		return new EditProduct();
	}
	else if (command == "fire_cashier")
	{
		return new FireCashier();
	}
	else if (command == "leave")
	{
		return new Leave();
	}
	else if (command == "list_categories")
	{
		return new ListCategories();
	}
	else if (command == "list_employees")
	{
		return new ListEmployees();
	}
	else if (command == "list_giftcards")
	{
		return new ListGiftCards();
	}
	else if (command == "list_products")
	{
		return new ListProducts();
	}
	else if (command == "list_products_by_category")
	{
		return new ListProductsByCategory();
	}
	else if (command == "list_transactions")
	{
		return new ListTransactions();
	}
	else if (command == "list_user_data")
	{
		return new ListUserData();
	}
	else if (command == "login")
	{
		return new Login();
	}
	else if (command == "logout")
	{
		return new Logout();
	}
	else if (command == "register")
	{
		return new Register();
	}
	else if (command == "list_pending")
	{
		return new ListPending();
	}
	else if (command == "list_warned_cashiers")
	{
		return new ListWarnedCashiers();
	}
	else if (command == "load_giftcards")
	{
		return new LoadGiftCards();
	}
	else if (command == "load_products")
	{
		return new LoadProducts();
	}
	else if (command == "promote_cashier")
	{
		return new PromoteCashier();
	}
	else if (command == "warn_cashier")
	{
		return new WarnCashier();
	}
	else if (command == "help")
	{
		return new Help();
		}

	return nullptr;
}
