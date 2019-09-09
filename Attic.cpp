/*******************************************************************************
** Program: homeInvasion
** File:    Attic.cpp
** -----------------------------------------------------------------------------
** This is the Attic class function implementation file. Attic is derived from
** the Space class.
*******************************************************************************/

char Attic::spaceMenu() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;
	Menu atticMenu;

	// if intruder has been defeated
	if (obtainedSpecial) {
		// add menu options
		atticMenu.addOption("Search room");
		atticMenu.addOption("Go down to the LIVING ROOM");
		atticMenu.addOption("Manage Inventory");
		atticMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		atticMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, atticMenu.getMenuSize());
		cout << endl;

		if (choice == 1)
			return '?';
		else if (choice == 2)
			return 'S';
		else if (choice == 3)
			return 'I';
		else
			return 'Q';
	}
	// intruder not defeated
	else {
		// add menu options
		atticMenu.addOption("Fight INTRUDER");
		atticMenu.addOption("Escape to the LIVING ROOM");
		atticMenu.addOption("Manage Inventory");
		atticMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		atticMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, atticMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '!';
		}
		else if (choice == 2) {
			return 'S';
		}
		else if (choice == 3) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
}

/*
** Displays a room-specific introduction.
*******************************************************************************/
void Attic::spaceIntro() {
	using std::cout;
	using std::endl;

	// intruder defeated
	if (obtainedSpecial)
		cout << "The INTRUDER lies on the floor unconscious... or dead." << endl;
	// intruder not defeated
	else
		cout << "The INTRUDER stares at you. They look ready to strike!" << endl;
}