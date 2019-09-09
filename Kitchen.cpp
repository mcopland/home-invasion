/*******************************************************************************
** Program: homeInvasion
** File:    Kitchen.cpp
** -----------------------------------------------------------------------------
** This is the Kitchen class function implementation file. Kitchen is derived
** from the Space class.
*******************************************************************************/

#include "Kitchen.hpp"

/*
** Displays a room-specific menu for interaction. The menu changes based on
** certain acquired items.
*******************************************************************************/
char Kitchen::spaceMenu() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;
	Menu kitchenMenu;

	// if lights are off
	if (!lightsOn) {

		// add menu options
		kitchenMenu.addOption("Look around the room");
		kitchenMenu.addOption("Return to the LIVING ROOM");
		kitchenMenu.addOption("Manage Inventory");
		kitchenMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		kitchenMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, kitchenMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '~';
		}
		else if (choice == 2) {
			return 'E';
		}
		else if (choice == 3) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if pantry is locked and user has the PANTRY-KEY
	else if (!pantryUnlocked && obtainedRequired) {
		// add menu options
		kitchenMenu.addOption("Unlock the PANTRY");
		kitchenMenu.addOption("Search the KITCHEN");
		kitchenMenu.addOption("Return to the LIVING ROOM");
		kitchenMenu.addOption("Manage Inventory");
		kitchenMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		kitchenMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, kitchenMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '!';
		}
		else if (choice == 2) {
			return '?';
		}
		else if (choice == 3) {
			return 'E';
		}
		else if (choice == 4) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if pantry is locked
	else if (!pantryUnlocked) {
		// add menu options
		kitchenMenu.addOption("Examine Knife");
		kitchenMenu.addOption("Search the room");
		kitchenMenu.addOption("Return to the LIVING ROOM");
		kitchenMenu.addOption("Manage Inventory");
		kitchenMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		kitchenMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, kitchenMenu.getMenuSize());
		cout << endl;
		
		if (choice == 1) {
			return '!';
		}
		else if (choice == 2) {
			return '?';
		}
		else if (choice == 3) {
			return 'E';
		}
		else if (choice == 4) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if pantry is unlocked, but user doesn't have the KNIFE
	else if (!obtainedSpecial) {
		// add menu options
		kitchenMenu.addOption("Examine Knife");
		kitchenMenu.addOption("Search the room");
		kitchenMenu.addOption("Leave room");
		kitchenMenu.addOption("Manage Inventory");
		kitchenMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		kitchenMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, kitchenMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '!';
		}
		else if (choice == 2) {
			return '?';
		}
		else if (choice == 3) {
			// create menu and add options
			Menu kitchenSubMenu;
			kitchenSubMenu.addOption("Right to the LIVING ROOM");
			kitchenSubMenu.addOption("Over to the PANTRY");

			cout << string(50, '-') << "+" << endl;
			cout << "Where would you like to go?\n" << endl;
			kitchenSubMenu.printMenu();
			cout << "+" << string(50, '-') << "+\n" << endl;

			cout << "Enter your selection: ";
			choice = getValidInt(1, kitchenSubMenu.getMenuSize());
			cout << endl;

			if (choice == 1) {
				return 'E';
			}
			else if (choice == 2) {
				return 'S';
			}
		}
		else if (choice == 4) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if user has the KNIFE
	else {
		// add menu options
		kitchenMenu.addOption("Search room");
		kitchenMenu.addOption("Leave room");
		kitchenMenu.addOption("Manage Inventory");
		kitchenMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		kitchenMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, kitchenMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '?';
		}
		else if (choice == 2) {
			// create menu and add options
			Menu kitchenSubMenu;
			kitchenSubMenu.addOption("Right to the LIVING ROOM");
			kitchenSubMenu.addOption("Over to the PANTRY");

			cout << string(50, '-') << "+" << endl;
			cout << "Where would you like to go?\n" << endl;
			kitchenSubMenu.printMenu();
			cout << "+" << string(50, '-') << "+\n" << endl;

			cout << "Enter your selection: ";
			choice = getValidInt(1, kitchenSubMenu.getMenuSize());
			cout << endl;

			if (choice == 1) {
				return 'E';
			}
			else if (choice == 2) {
				return 'S';
			}
		}
		// manage inventory
		else if (choice == 4) {
			return 'I';
		}
		// quit game
		else {
			return 'Q';
		}
	}
}

/*
** Displays a room-specific introduction.
*******************************************************************************/
void Kitchen::spaceIntro() {
	using std::cout;
	using std::endl;

	// if lights are off
	if (!lightsOn) {
		cout << "It's too dark. You can't see a thing!" << endl;
	}
	// if pantry is locked and user has the PANTRY-KEY
	else if (!pantryUnlocked && obtainedRequired) {
		cout << "You see the pantry, but it appears to be locked. Where could the key be?" << endl;
	}
	// if pantry is unlocked, but user doesn't have KNIFE
	else if (!pantryUnlocked || !obtainedSpecial) {
		cout << "There's a KNIFE! That could be useful." << endl;
	}
	// if user has KNIFE
	else {
		cout << "All that's left are some cookbooks. Where are the pots and pans?" << endl;
	}
}