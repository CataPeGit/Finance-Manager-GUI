#pragma once

#include "Repository.h"

class Action : public Repository{
	friend class Logic;
public:

	Action(int _type, User _user_action);

	// function used to redo/undo operations based on a switch

	User get_user_action();

	// undo function
	//void undo_operation();

	// redo function
	//void redo_operation();

private:

	// type of the function that we have to undo/redo
	int type;
	// User variable manipulated based on the type 
	User user_action;
};


