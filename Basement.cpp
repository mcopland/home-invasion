/*******************************************************************************
** Program: homeInvasion
** File:    Basement.cpp
** -----------------------------------------------------------------------------
** This is the Basement class function implementation file. Basement is derived
** from the Space class.
*******************************************************************************/

#include "Basement.hpp"

/*
** Displays a room-specific menu for interaction. The menu changes based on
** certain acquired items.
*******************************************************************************/
char Basement::spaceMenu() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	// if lights are off
	if (!lightsOn) {
		// create menu and add options
		Menu basementMenu;
		basementMenu.addOption("Look around the room");
		basementMenu.addOption("Return to the LIVING ROOM");
		basementMenu.addOption("Manage Inventory");
		basementMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		basementMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, basementMenu.getMenuSize());
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
	// if lights are on
	else {
		// create menu and add options
		Menu basementMenu;
		basementMenu.addOption("Look for anything useful");
		basementMenu.addOption("Return to the LIVING ROOM");
		basementMenu.addOption("Manage Inventory");
		basementMenu.addOption("Quit Game");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "What would you like to do?\n" << endl;
		basementMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, basementMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			return '!';
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
void Basement::spaceIntro() {
	using std::cout;
	using std::endl;

	// if lights are off and user doesn't have FLASHLIGHT
	if (!lightsOn && !obtainedRequired) {
		cout << "It's too dark. You can't see a thing!" << endl;
	}
	// if lights are off and user has FLASHLIGHT
	else if (!lightsOn) {
		cout << "It's dark in here. Thankfully I have this FLASHLIGHT." << endl;
	}
	// if lights are on
	else {
		cout << "What a surprise. Another mess." << endl;
	}
}