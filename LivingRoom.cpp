/*******************************************************************************
** Program: homeInvasion
** File:    LivingRoom.cpp
** -----------------------------------------------------------------------------
** This is the LivingRoom class function implementation file.  LivingRoom is
** derived from the Space class.
*******************************************************************************/

#include "LivingRoom.hpp"

/*
** Displays a room-specific menu for interaction. The menu changes based on
** certain acquired items.
*******************************************************************************/
char LivingRoom::spaceMenu() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	// create menu and add options
	Menu livingRoomMenu;
	livingRoomMenu.addOption("Examine the bag of batteries");
	livingRoomMenu.addOption("Search room");
	livingRoomMenu.addOption("Leave room");
	livingRoomMenu.addOption("Manage Inventory");
	livingRoomMenu.addOption("Quit Game");

	cout << "\n+" << string(50, '-') << "+" << endl;
	cout << "What would you like to do?\n" << endl;
	livingRoomMenu.printMenu();
	cout << "+" << string(50, '-') << "+\n" << endl;

	cout << "Enter your selection: ";
	choice = getValidInt(1, livingRoomMenu.getMenuSize());
	cout << endl;

	if (choice == 1)
		return '!';
	else if (choice == 2)
		return '?';
	else if (choice == 3) {
		// create menu and add options
		Menu livingRoomExitMenu;
		livingRoomExitMenu.addOption("Right to the BEDROOM");
		livingRoomExitMenu.addOption("Left to the KITCHEN");
		livingRoomExitMenu.addOption("Down to the BASEMENT");
		livingRoomExitMenu.addOption("Up to the ATTIC");

		cout << string(50, '-') << "+" << endl;
		cout << "Where would you like to go?\n" << endl;
		livingRoomExitMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, livingRoomExitMenu.getMenuSize());
		cout << endl;

		if (choice == 1)
			return 'E';
		else if (choice == 2)
			return 'W';
		else if (choice == 3)
			return 'S';
		else
			return 'N';
	}
	// manage inventory
	else if (choice == 4)
		return 'I';
	// quit game
	else 
		return 'Q';
}

/*
** Displays a room-specific introduction.
*******************************************************************************/
void LivingRoom::spaceIntro() {
	using std::cout;
	using std::endl;

	cout << "You look around the room to see items thrown about the place.\n"
		<< "Empty beer cans, a bag of batteries, and several pizza boxes.\n"
		<< "This place is a mess, but you need to find something to defend yourself."
		<< endl;
}