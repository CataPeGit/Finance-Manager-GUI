#include "User.h"


// Rule of three
User::User() {
	id = NULL;
	name = "";
	account_balance = 0;
	purchased_price[""] = NULL;
}
User::User(const User& other_user) {
	id = other_user.get_id();
	name = other_user.get_name();
	account_balance = other_user.get_account_balance();
	purchased_price = other_user.get_purchased_price();
}
User::~User() {

}

User::User(unsigned int _id, string _name, unsigned int _account_balance) {
	id = _id;
	name = _name;
	account_balance = _account_balance;
}


// getters
unsigned int User::get_id() const {
	return id;
}
string User::get_name() const {
	return name;
}

unsigned int User::get_account_balance() const {
	return account_balance;
}

std::map<std::string, unsigned int> User::get_purchased_price() const {
	return purchased_price;
}

unsigned int User::get_specific_purchase_price(string item_name) {
	return purchased_price[item_name];
}

unsigned int User::get_total_balance_spent() {
	// looping trough the map and calculating the total balance spent
	unsigned int spent = 0;
	for (auto& key_value : purchased_price) {
		spent += key_value.second;
	}
	return spent;
}


// setters
void User::set_specific_purchase_price(string item_name, unsigned int new_price) {
	purchased_price[item_name] = new_price;
}

void User::set_all_new_purchase_prices(std::map<std::string, unsigned int> _new_prices) {
	purchased_price = _new_prices;
}

void User::set_balance(unsigned int new_balance)
{
	account_balance = new_balance;
}

void User::set_new_id(unsigned int new_id){
	id = new_id;
}


// modifiers
void User::add_to_balance(unsigned int value_to_add)
{
	account_balance += value_to_add;
}

void User::substract_from_balance(unsigned int substracted_value)
{
	account_balance -= substracted_value;
}

void User::add_purchase_to_map(string item_name, unsigned int item_price) {
	// add a new purchase to the purchases map without changing other information such as balance
	if (!check_if_purchase_exists(item_name)) {
		// item not found 
		purchased_price[item_name] = item_price;
	}
	else {
		// item found
		purchased_price[item_name] += item_price;
	}
}

void User::purchase_item(string item_name, unsigned int item_price){
	// modify user data based on new purchase 

	account_balance -= item_price;
	add_purchase_to_map(item_name, item_price);
}


void User::remove_purchase(string item_name) {
	// remove purchase from map
	if (check_if_purchase_exists(item_name)) {
		purchased_price.erase(item_name);
	}
	else {
		//std::cout << "Item not found/purchased";
		throw 404;
	}

}

bool User::check_if_purchase_exists(const string& item_name) {
	if (purchased_price.find(item_name) == purchased_price.end()) {
		// item not found
		return false;
	}
	// item found
	return true;
}


// view/display functions
void User::view_purchases() const {
	// looping trough and displaying the items in the map
	for (auto& key_value : purchased_price) {
		std::cout << key_value.first << ": " << key_value.second << std::endl;
	}
}


// operator overloads
ostream& operator<<(ostream& out, const User& user)
{
	// Output general information about the user
	out << "Id: " << user.get_id() << std::endl;
	out << "Name: " << user.get_name() << std::endl;
	out << "Account Balance: " << user.get_account_balance() << std::endl;

	bool found = false;
	map<string, unsigned int>::iterator it;
	std::map<std::string, unsigned int> purchase_map = user.get_purchased_price();
	for (it = purchase_map.begin(); it != purchase_map.end(); it++) {
		found = true;
		out << "Purchased " << it->first << " at the price of " << it->second << ".\n";
	}
	if (found == false)
		out << "No purchases.";
	out << "\n\n";
	return out;
}


bool User::operator==(const User& user)
{
	if (id != user.get_id())
		return false;
	if(name != user.get_name())
		return false;
	if(account_balance != user.get_account_balance())
		return false;
	if(purchased_price == user.get_purchased_price())
		return false;
	return true;
}

