#include "UI.h"

void displayMenu() {
	cout << "M|m     Display the menu" << "\n";
	cout << "A|a     Add user to the repository" << "\n"; // 1 punct
	cout << "U|u     Update user by id" << "\n"; // 0.5 punct
	cout << "R|r     Remove user by id" << "\n"; // 1 pct 
	
	cout << "D|d     Display all users" << "\n"; // 1 pct
	cout << "I|i     Display user by id" << "\n";

	cout << "B|b     Undo" << "\n";
	cout << "F|f     Redo" << "\n";

	cout << "S|s     Save (write data to file)" << "\n"; // 0.5 pct
	cout << "Q|q     Quit" << "\n" << "\n";
}
