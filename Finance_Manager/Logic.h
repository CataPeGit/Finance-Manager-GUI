#pragma once

#include "UI.h"
#include "Repository.h"
#include "Action.h"
#include <sstream>
#include <stack>
#include <vector>

using std::getline;
using std::cin;
using std::stack;
using std::vector;

class Logic {
	friend class Action;
public :

    Logic();
    ~Logic();

    void set_main_repository(Repository new_repository);
    Repository get_main_repository();

    void add_user_to_repository(string _name, unsigned int _account_balance);    // type 1
    void update_user_in_repository(unsigned int _id, std::pair<string, int> current_purchase); // type 2
    void remove_user_from_repository(string id_string); // type 3
	void display_all_users();         

    void set_balance_by_id(unsigned int _id, unsigned int new_balance);
    void set_name_by_id(unsigned int _id, string new_name);

    void write_to_file();
    void read_from_file();

    void display_user_by_id();

	void add_to_undo(Action last_action);
    void add_to_redo(Action new_action);

	void undo();
    void undo_operation(Action last_action);

	void redo();
	void redo_operation(Action last_action);


protected:
	Repository main_repository;
	stack<Action> undo_stack;
	stack<Action> redo_stack;

};

