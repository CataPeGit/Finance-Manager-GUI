#include "Repository.h"

Repository::Repository(){
}

Repository::Repository(const Repository& _other){
	user_repository = _other.user_repository;
}

Repository::~Repository(){
}

void Repository::operator=(Repository& other_repo){
    this->user_repository = other_repo.get_rep();
}

std::vector<User> Repository::get_rep() const
{
	return user_repository;
}

unsigned int Repository::get_size() const
{
	return user_repository.size();
}

User Repository::get_user_by_id(unsigned int _id) const
{
	return user_repository.at(_id-1);
}

void Repository::update_user_by_id(User updated_user){
	user_repository.at(updated_user.get_id()-1) = updated_user;
}

void Repository::remove_user_by_id(unsigned int _id){
	// removes the user having the given id
	// and if needed modifies other user id's
	user_repository.erase(user_repository.begin() + _id - 1);
	for (User user : user_repository) {
		if (user.get_id() > _id) {
			user.set_new_id(_id - 1);
		}
	}
}

void Repository::add_user_to_repository(User user){
	user_repository.push_back(user);
}

void Repository::remove_user_from_repository(User user){
	// search trough the repository for the user by id user and remove him 
	remove_if(
		user_repository.begin(),
		user_repository.end(),
		[user](User user_in_rep) {
			if (user.get_id() == user_in_rep.get_id()) {
				return true;
			}
			return false;
		}
	);
}

void Repository::change_user_balance_by_id(unsigned int _id, unsigned new_balance){

    for(User& current_user: user_repository){
        if(current_user.get_id() == _id){
            current_user.set_balance(new_balance);
            break;
        }
    }

}

void Repository::clear_repository(){
	user_repository.clear();
}

void Repository::user_purchase_item_by_id(unsigned int _id, string new_item_name, unsigned int new_item_price){
    user_repository.at(_id-1).purchase_item(new_item_name, new_item_price);
}

vector<string> tokenize(string str, char delimiter)
{
	// tokenize a given string based on a delimiter
	// usage example: tokanize types of user data in order to save from/to repository 
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}

unsigned int Repository::get_available_id(){
    // returns an available id based on the current user id's
    std::vector<unsigned int> all_ids;
    for(User current_user: user_repository){
        all_ids.push_back(current_user.get_id());
    }

    unsigned int _id = 1;
    while(true){
        if (std::find(all_ids.begin(), all_ids.end(), _id) != all_ids.end()){
            _id++;
        }
        else{
            break;
        }
    }

    return _id;
}

void Repository::read_from_file()
{
	// reading the data file and saving all user information into repositoy
	ifstream data_file;
	data_file.open("data.csv");

	string line_information;
	while (getline(data_file, line_information)) {
		// Output the text from the file
		vector<string> data = tokenize(line_information, ',');
		User new_user(std::stoi(data[0]), data[1], std::stoi(data[2]));
		
		// we need to treat the purchases map separately
		// one purchase will be represented by an item name and price, one next to the other
		int i = 3;
		while (i < data.size()) {
			new_user.add_purchase_to_map(data[i], std::stoi(data[i+1]));
			i += 2;
		}
		
        user_repository.push_back(new_user);
		line_information.clear();
	}
	data_file.close();
}

void Repository::write_to_file() {
	// writing data from the repository to the data file
	ofstream data_file;
	data_file.open("data.csv");

	for (User current_user : user_repository) {
		data_file << current_user.get_id() << "," << current_user.get_name() << "," << current_user.get_account_balance();
		std::map<std::string, unsigned int> current_user_purchases = current_user.get_purchased_price();
		
		map<string, unsigned int>::iterator it;
		for (it = current_user_purchases.begin(); it != current_user_purchases.end(); it++)
		{
			if (it == current_user_purchases.begin())
				data_file << ",";
			data_file << it->first << "," << it->second << ",";
		}

		data_file << "\n";
	}

	data_file.close();
}

