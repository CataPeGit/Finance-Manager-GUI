#include "Logic.h"
#include <fstream>
#include <string>

Logic::Logic()
{
}
Logic::~Logic()
{
}

void Logic::set_main_repository(Repository new_repository){
    main_repository = new_repository;
}
Repository Logic::get_main_repository(){
    return main_repository;
}

void Logic::add_user_to_repository(string _name, unsigned int _account_balance) {
    unsigned int _id = main_repository.get_available_id();
    User new_user(_id, _name, _account_balance);
    undo_stack.push(Action(1, new_user));
	main_repository.add_user_to_repository(new_user);
}

void Logic::update_user_in_repository(unsigned int _id, std::pair<string, int> current_purchase){
    // taking the current user data from UI and updating the user
    for(User& user : main_repository.get_rep()){
        if(user.get_id() == _id){
            user.purchase_item(current_purchase.first, current_purchase.second);
            undo_stack.push(Action(2, user));
            main_repository.update_user_by_id(user);
        }
    }
}

void Logic::set_name_by_id(unsigned int _id, string new_name){
    //changing user name based on id
    for(User& current_user : main_repository.get_rep()){
        if(current_user.get_id() == _id){
            current_user.set_name(new_name);
            break;
        }
    }
}

void Logic::set_balance_by_id(unsigned int _id, unsigned int new_balance){
    //changing user balance based on id
    for(User& current_user : main_repository.get_rep()){
        if(current_user.get_id() == _id){
            current_user.set_balance(new_balance);
            break;
        }
    }
}

void Logic::remove_user_from_repository(string id_string){
    // add user to the undo stack
    // and remove the user from the repository
    int position = 0;
    for(User& current_user: main_repository.get_rep()){
        if(current_user.get_id() == (unsigned int)std::stoi(id_string)){
            break;
        }
        position++;
    }

    undo_stack.push(Action(3, main_repository.get_user_by_id(position)));
    main_repository.remove_user_by_id(std::stoi(id_string));
}

void Logic::display_all_users(){
	for (User user : main_repository.get_rep()) {
		cout << user;
	}
}

void Logic::write_to_file() {
	main_repository.write_to_file();
}

void Logic::read_from_file() {
    main_repository.read_from_file();
}

void Logic::display_user_by_id(){
	cout << "User id: ";
	string id_string;
	getline(cin, id_string);
	try {
        for (unsigned long long int i = 0; i < id_string.length(); i++) {
			if (id_string[i] != '9' && id_string[i] != '8' && id_string[i] != '7' && id_string[i] != '6' && id_string[i] != '5' && id_string[i] != '4' && id_string[i] != '3' && id_string[i] != '2' && id_string[i] != '1' && id_string[i] != '0')
			{
				throw 252;
			}
		}
	}
	catch (int) {
		cout << "You must enter a number bigger than 0.";
		return;
	}
	unsigned int _id = stoi(id_string);
	cout << main_repository.get_user_by_id(_id);
}

void Logic::add_to_undo(Action last_action) {
	undo_stack.push(last_action);
}

void Logic::add_to_redo(Action new_action){
    redo_stack.push(new_action);
}

void Logic::undo() {
	// pops last action from the stack into redo
	if (undo_stack.empty() == false) {
		Action last_action = undo_stack.top();
		undo_stack.pop();
		undo_operation(last_action);
		redo_stack.push(last_action);
	}
}

void Logic::undo_operation(Action last_action) {
	// apply undo directly
	// using switch to apply the proper command
	switch (last_action.type) {
	case 1:
		main_repository.remove_user_by_id(last_action.user_action.get_id());
		break;
	case 2:
		main_repository.update_user_by_id(last_action.get_user_action());
		break;
	case 3:
		main_repository.add_user_to_repository(last_action.get_user_action());
		break;
	default:
		printf("Operation not available.");
		break;
	}
}

void Logic::redo()
{
	if (redo_stack.empty() == false) {
		Action last_action = redo_stack.top();
		redo_stack.pop();
		redo_operation(last_action);
		undo_stack.push(last_action);
	}
}

void Logic::redo_operation(Action last_action) {
	switch (last_action.type) {
	case 1:
		main_repository.add_user_to_repository(last_action.get_user_action());
		break;
	case 2:
		main_repository.update_user_by_id(last_action.get_user_action());
		break;
	case 3:
		main_repository.remove_user_by_id(last_action.user_action.get_id());
		break;
	default:
		printf("Operation not available.");
		break;
	}
}



