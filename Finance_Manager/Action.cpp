#include "Action.h"



Action::Action(int _type, User _user_action) {
	type = _type;
    user_action = _user_action;
}

User Action::get_user_action()
{
    return user_action;
}

