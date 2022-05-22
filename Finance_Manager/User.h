#pragma once
#include <string>
#include <map>
#include <ostream>
#include <iostream>

using std::string;
using std::map;
using std::ostream;
using std::istream;

class Repository;

//template<typename ElementType>

class User {

	friend class Repository;

public:

	// Rule of three
	User();
	User(const User& other_user);
	~User();

	User(unsigned int _id, string _name, unsigned int _account_balance);


	// getters
	unsigned int get_id() const;
	string get_name() const;
	unsigned int get_account_balance() const;
	std::map<std::string, unsigned int> get_purchased_price() const;

	unsigned int get_specific_purchase_price(string item_name);
	unsigned int get_total_balance_spent();

	// setters
	void set_specific_purchase_price(string item_name, unsigned int new_price);
	void set_all_new_purchase_prices(std::map<std::string, unsigned int> _new_prices);
	void set_balance(unsigned int new_balance);
	void set_new_id(unsigned int new_id);

	// modifiers
	void add_to_balance(unsigned int value_to_add);
	void substract_from_balance(unsigned int substracted_value);

	void add_purchase_to_map(string item_name, unsigned int item_price);

	void purchase_item(string item_name, unsigned int item_price);

	void remove_purchase(string item_name);
	bool check_if_purchase_exists(const string& item_name);

	// view/display functions
	void view_purchases() const;

	bool operator==(const User& user);

	// operator overloads
	friend ostream& operator<<(ostream& out, const User& user);

	//void operator=(User& user);
	

private:
	// user id
	unsigned int id;

	// name of the user
	string name;

	// the current balance of the user
	unsigned int account_balance;

	// mapping items purchased by the user to their price
	// in order to keep track of what items the user bought and the money they spent
	std::map<std::string, unsigned int> purchased_price;
};

