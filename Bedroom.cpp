/*******************************************************************************
** Program: homeInvasion
** File:    Bedroom.cpp
** -----------------------------------------------------------------------------
** This is the Bedroom class function implementation file. Bedroom is derived
** from the Space class.
*******************************************************************************/

#include "Bedroom.hpp"

/*
** Displays a room-specific menu for interaction. The menu changes based on
** certain acquired items.
*******************************************************************************/
char Bedroom::spaceMenu() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	// if lights are off and user doesn't have the DEAD-FLASHLIGHT
	if (!lightsOn && !obtainedSpecial) {
		// create menu and add options
		Menu bedroomMenu;
		bedroomMenu.addOption("Grab the DEAD-FLASHLIGHT");
		bedroomMenu.addOption("Return to the LIVING ROOM");
		bedroomMenu.addOption("Manage Inventory.");
		bedroomMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		bedroomMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, bedroomMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '!';
		}
		else if (choice == 2) {
			return 'W';
		}
		else if (choice == 3) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if lights are off
	else if (!lightsOn) {
		// create menu and add options
		Menu bedroomMenu;
		bedroomMenu.addOption("Look around the room");
		bedroomMenu.addOption("Return to the LIVING ROOM");
		bedroomMenu.addOption("Manage Inventory");
		bedroomMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		bedroomMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, bedroomMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '~';
		}
		else if (choice == 2) {
			return 'W';
		}
		else if (choice == 3) {
			return 'I';
		}
		else {
			return 'Q';
		}
	}
	// if lights are on
	else {
		// create menu and add options
		Menu bedroomMenu;
		bedroomMenu.addOption("Search room");
		bedroomMenu.addOption("Return to the LIVING ROOM");
		bedroomMenu.addOption("Manage Inventory");
		bedroomMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		bedroomMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, bedroomMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '?';
		}
		else if (choice == 2) {
			return 'W';
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
void Bedroom::spaceIntro() {
	using std::cout;
	using std::endl;

	// if lights are off and user doesn't have the DEAD-FLASHLIGHT
	if (!lightsOn && !obtainedSpecial) {
		cout << "It's dark in here, but you can see a DEAD-FLASHLIGHT on the nightstand." << endl;
	}
	// if lights are off
	else if (!lightsOn) {
		cout << "It's too dark. You can't see a thing!" << endl;
	}
	// if lights are on
	else {
		cout << "My bedroom. I wonder if there's anything I could use in here." << endl;
	}
}