#pragma once

#include "User.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::map;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;

class Repository {
	friend class User;
public:
	friend vector<string> tokenize(string str, char delimiter);
	Repository();
	Repository(const Repository& _other);
	~Repository();

	std::vector<User> get_rep() const;
	unsigned int get_size() const;
	User get_user_by_id(unsigned int _id) const;

   	void user_purchase_item_by_id(unsigned int _id, string new_item_name, unsigned int new_item_price);

	void update_user_by_id(User updated_user);
	void remove_user_by_id(unsigned int _id);

 	void change_user_balance_by_id(unsigned int _id, unsigned new_balance);

   	unsigned int get_available_id();
	bool is_user_in_repository(unsigned int _id);

	void add_user_to_repository(User user);
	void remove_user_from_repository(User user);
	void clear_repository();

	void read_from_file();
	void write_to_file();

    	void operator=(Repository& other_repo);

private:
	std::vector<User> user_repository;
};
