/*******************************************************************************
** Program: homeInvasion
** File:    Pantry.cpp
** -----------------------------------------------------------------------------
** This is the Pantry class function implementation file. Pantry is derived
** from the Space class.
*******************************************************************************/

#include "Pantry.hpp"

/*
** Displays a room-specific menu for interaction. The menu changes based on
** certain acquired items.
*******************************************************************************/
char Pantry::spaceMenu() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;
	Menu pantryMenu;

	// if lights are off
	if (!lightsOn) {
		// add menu options
		pantryMenu.addOption("Look around the room");
		pantryMenu.addOption("Return to the KITCHEN");
		pantryMenu.addOption("Manage Inventory");
		pantryMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		pantryMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, pantryMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '~';
		}
		else if (choice == 2) {
			return 'N';
		}
		else if (choice == 3) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if lights are on, but chest isn't open
	else if (!obtainedSpecial) {
		// add menu options
		pantryMenu.addOption("Look at the trashcan");
		pantryMenu.addOption("Search room");
		pantryMenu.addOption("Return to the KITCHEN");
		pantryMenu.addOption("Manage Inventory");
		pantryMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		pantryMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, pantryMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '!';
		}
		else if (choice == 2) {
			return '?';
		}
		else if (choice == 3) {
			return 'N';
		}
		else if (choice == 4) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if lights are on and the chest has been opened
	else {
		// add menu options
		pantryMenu.addOption("Search room");
		pantryMenu.addOption("Return to the KITCHEN");
		pantryMenu.addOption("Manage Inventory");
		pantryMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		pantryMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, pantryMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '?';
		}
		else if (choice == 2) {
			return 'N';
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
void Pantry::spaceIntro() {
	using std::cout;
	using std::endl;

	// if lights are off
	if (!lightsOn)
		cout << "It's too dark. You can't see a thing!" << endl;
	// if lights are on and the trashcan hasn't been opened
	else if (!obtainedSpecial) {
		cout << "There isn't much besides a metal trashcan and ramen packets." << endl;
	}
	// if lights are on and the chest has been opened
	else
		cout << "There doesn't seem to be much else of use." << endl;
}