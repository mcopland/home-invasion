/*******************************************************************************
** Program: homeInvasion
** File:    Game.cpp
** -----------------------------------------------------------------------------
** This is the Game class function implementation file. The Game class manages
** the gameplay rules and logic while tracking the user's characteristics.
*******************************************************************************/

#include "Game.hpp"

/*
** Constructor for Game class. Creates and links the six Space objects and
** initializes the user status.
*******************************************************************************/
Game::Game() {
	// create Spaces
	attic = new Attic("ATTIC");
	basement = new Basement("BASEMENT");
	bedroom = new Bedroom("BEDROOM");
	kitchen = new Kitchen("KITCHEN");
	livingRoom = new LivingRoom("LIVING ROOM");
	pantry = new Pantry("PANTRY");
	
	// link Spaces
	attic->setPointer('S', livingRoom);
	basement->setPointer('N', livingRoom);
	bedroom->setPointer('W', livingRoom);
	kitchen->setPointer('E', livingRoom);
	kitchen->setPointer('S', pantry);
	livingRoom->setPointer('E', bedroom);
	livingRoom->setPointer('W', kitchen);
	livingRoom->setPointer('N', attic);
	livingRoom->setPointer('S', basement);	
	pantry->setPointer('N', kitchen);
	
	// initialize user
	health = 100;
	threatLevel = 0;
	location = livingRoom;
	isDead = false;
	gameWon = false;
	
    // seed RNG
    srand(static_cast<unsigned>(std::time(0)));
}

/*
** The main loop that runs through the entire game. Allows the user to traverse
** the map while searching rooms, collecting items, and fighting the end boss.
** This continues until the user quits, dies, runs out of time, or beats the
** game.
*******************************************************************************/
void Game::play() {
	using std::cout;
	using std::endl;

	char value;

	do {
		// display room intro and menu
		location->spaceIntro();
		value = location->spaceMenu();

		if (value == 'N') {
			location = location->getNorth();
		}
		else if (value == 'S') {
			location = location->getSouth();
		}
		else if (value == 'E') {
			location = location->getEast();
		}
		else if (value == 'W') {
			location = location->getWest();
		}
		// special room
		else if (value == '!') {
			if (location == livingRoom) {
				specialLivingRoom();
			}
			else if (location == bedroom) {
				specialBedroom();
			}
			else if (location == kitchen) {
				specialKitchen();
			}
			else if (location == pantry) {
				specialPantry();
			}
			else if (location == basement) {
				specialBasement();
			}
			else if (location == attic) {
				specialAttic();
			}
		}
		// search room
		else if (value == '?') {
			if (location == livingRoom) {
				searchLivingRoom();
			}
			else if (location == bedroom) {
				searchBedroom();
			}
			else if (location == kitchen) {
				searchKitchen();
			}
			else if (location == pantry) {
				searchPantry();
			}
			else if (location == attic) {
				searchAttic();
			}
		}
		// manage inventory
		else if (value == 'I') {
			removeItem();
		}
		// turn lights on
		else if (value == '~') {
			if (searchInventory("FLASHLIGHT")) {
				cout << "You use your FLASHLIGHT to light up the ";
				cout << location->getName() << ".\n" << endl;

				location->setLightsOn(true);
			}
			else {
				cout << "It looks like the power's out. If only I had a light "
					<< "source...\n" << endl;
			}
		}

		// check player status
		if (isDead) {
			cout << "You are dead." << endl;
		}

		// increment game timer
		threatLevel++;

		// check time
		if (threatLevel == 10) {
			cout << "You hear the INTRUDER shuffling about. You must hurry!\n" << endl;
		}
		else if (threatLevel == 30) {
			cout << "The INTRUDER seems to be getting anxious. They may come "
				<< "down if you don't hurry!" << endl;
		}
		else if (threatLevel == 50) {
			cout << "You turn around to see the INTRUDER. They strike and you "
				<< "fall to the ground.\n"
				<< "INTRUDER: \"You were\'nt supposed to be here.\"" << endl;
			isDead = true;
		}

	} while (value != 'Q' && !isDead && !gameWon);

	// display results
	if (gameWon) {
		winScreen();
	}
	else {
		loseScreen();
	}

	// deallocate memory
	delete attic;
    delete basement;
    delete bedroom;
    delete kitchen;
    delete livingRoom;	
	delete pantry;
}

/*
** Special situation for the LivingRoom. Provides the FLASHLIGHT and lights the
** other rooms.
*******************************************************************************/
void Game::specialLivingRoom() {
	using std::cout;
	using std::endl;

	// if user has FLASHLIGHT
	if (searchInventory("FLASHLIGHT")) {
		cout << "These batteries are a bit light to be used as a weapon.\n" << endl;
	}
	// if user has DEAD-FLASHLIGHT
	else {
		if (searchInventory("DEAD-FLASHLIGHT")) {
			cout << "You put fresh batteries in the DEAD-FLASHLIGHT. It works!" << endl;
			cout << "ITEM OBTAINED: FLASHLIGHT\n" << endl;

			inventory.push_back("FLASHLIGHT");
			inventory.remove("DEAD-FLASHLIGHT");

			livingRoom->setObtainedSpecial(true);
			basement->setObtainedRequired(true);
		}
		else {
			cout << "Batteries. Maybe there's a FLASHLIGHT around here somewhere?\n" << endl;
		}
	}
}

/*
** Special situation for the Bedroom. Provides the DEAD-FLASHLIGHT for future use.
*******************************************************************************/
void Game::specialBedroom() {
	using std::cout;
	using std::endl;

	// if inventory is full
	if (inventory.size() == MAX_INVENTORY) {
		cout << "You're overburdened! Manage your Inventory." << endl;
	}
	else {
		cout << "You grab the DEAD-FLASHLIGHT. This could be useful." << endl;
		cout << "ITEM OBTAINED: DEAD-FLASHLIGHT\n" << endl;

		inventory.push_back("DEAD-FLASHLIGHT");

		bedroom->setObtainedSpecial(true);
		livingRoom->setObtainedRequired(true);
	}
}

/*
** Special situation for the Kitchen. Provides the KNIFE and access to the locked
** PANTRY if user has found the PANTRY-KEY.
*******************************************************************************/
void Game::specialKitchen() {
	using std::cout;
	using std::endl;

	// if user has PANTRY-KEY
	if (!location->getPantryUnlocked() && searchInventory("PANTRY-KEY")) {
		cout << "You unlock the PANTRY with the PANTRY-KEY.\n"
			<< "You step inside to check it out.\n" << endl;

		kitchen->setPantryUnlocked(true);
		location = location->getSouth();

		inventory.remove("PANTRY-KEY");
	}
	// if pantry is unlocked, but user doesn't have TRASHCAN-LID
	else if (!location->getPantryUnlocked() || !searchInventory("TRASHCAN-LID")) {
		cout << "The KNIFE is stuck in the countertop. You're going to need "
			<< "something heavy to help wedge it out.\n" << endl;
	}
	// if user has TRASHCAN-LID
	else {
		if (inventory.size() == MAX_INVENTORY) {
			cout << "This TRASHCAN-LID could help free the KNIFE, but your inventory is full." << endl;
		}
		else {
			cout << "You use the TRASHCAN-LID to wedge the knife out of the countertop.\n" << endl;
			cout << "ITEM OBTAINED: KNIFE\n" << endl;

			inventory.push_back("KNIFE");

			kitchen->setObtainedSpecial(true);
		}
	}
}

/*
** Special situation for the Pantry. Provides the TRASHCAN-LID for defense and
** the ability to unlock the KNIFE in the Kitchen.
*******************************************************************************/
void Game::specialPantry() {
	using std::cout;
	using std::endl;

	// if inventory is full
	if (inventory.size() == MAX_INVENTORY) {
		cout << "You eye the TRASHCAN-LID, but your inventory is full..." << endl;
	}
	else {
		cout << "You grab the TRASHCAN-LID!" << endl;
		cout << "This should help you defend yourself.\n" << endl;
		cout << "ITEM OBTAINED: TRASHCAN-LID\n" << endl;

		inventory.push_back("TRASHCAN-LID");

		pantry->setObtainedSpecial(true);
	}
}

/*
** Special situation for the Basement. Provides the means for escape if the user
** has defeated the INTRUDER and obtained the BASEMENT-KEY.
*******************************************************************************/
void Game::specialBasement() {
	using std::cout;
	using std::endl;

	// if user has BASEMENT-KEY
	if (searchInventory("BASEMENT-KEY")) {
		cout << "The BASEMENT-KEY unlocks the only exit from the house."
			<< " Boarding up everything else proved to be a bad decision.\n" << endl;
		cout << "You escape with your life!\n" << endl;
		gameWon = true;
	}
	// if user doesn't have PANTRY-KEY
	else if (!basement->getObtainedSpecial()) {
		cout << "You see something shiny as you enter the BASEMENT. It's a key!\n" << endl;

		if (inventory.size() == MAX_INVENTORY) {
			cout << "...But your Inventory is full.\n" << endl;
		}
		else {
			inventory.push_back("PANTRY-KEY");
			cout << "ITEM OBTAINED: PANTRY-KEY\n" << endl;

			basement->setObtainedSpecial(true);
			kitchen->setObtainedRequired(true);
		}
	}
	// if user has the KNIFE and TRASHCAN-LID
	else if (searchInventory("KNIFE") && ("TRASHCAN-LID")) {
		cout << "You've got a weapon and a makeshift shield. You should take out the INTRUDER." << endl;
	}
	else if (searchInventory("TRASHCAN-LID")) {
		cout << "You've got a makeshift shield. Now to find a weapon." << endl;
	}
	else if (!searchInventory("KNIFE") && !searchInventory("TRASHCAN-LID")) {
		cout << "Hiding down here sounds good, but it's only a matter of time "
			<< "before the INTRUDER comes looking for you.\n" << endl;
	}
}

/*
** Special situation for the Attic. Simulates the battle between the user and
** the INTRUDER.
*******************************************************************************/
void Game::specialAttic() {
	using std::cout;
	using std::endl;
	using std::string;

	bool intruderDead = false;
	int intruderHealth = 100;
	int attack;
	int defense;
	int choice = 0;

	do {
		// calculate attack/defense values
		attack = rand() % 4 + 1;
		defense = rand() % 3 + 1;

		cout << "INTRUDER'S HEALTH: " << intruderHealth << endl << endl;

		cout << "The INTRUDER swings their weapon at you." << endl;
		if (searchInventory("TRASHCAN-LID")) {
			if (defense == 1) {
				cout << "Your TRASHCAN-LID deflected some of the damage." << endl;
				health -= 10;
			}
			else if (defense == 2) {
				cout << "Your TRASHCAN-LID deflected most of the damage." << endl;
				health -= 5;
			}
			else {
				cout << "You block the INTRUDER's attack with the TRASHCAN-LID." << endl;
			}
		}
		else {
			cout << "You have no shield! This is going to hurt." << endl;
			health -= 25;
		}
		
		if (searchInventory("KNIFE")) {
			if (attack == 1) {
				cout << "You missed your attack!\n" << endl;
			}
			else if (attack == 2) {
				cout << "You did a small amount of damage with the KNIFE.\n" << endl;
				intruderHealth -= 10;
			}
			else if (attack == 3) {
				cout << "You did a good amount of damage with the KNIFE.\n" << endl;
				intruderHealth -= 25;
			}
			else {
				cout << "You did a large amount of damage with the KNIFE!\n" << endl;
				intruderHealth -= 50;
			}
		}
		else {
			cout << "You have no weapon to fight with!\n" << endl;
		}


		// check user and INTRUDER health
		if (intruderHealth <= 0 || health <= 0) {
			if (intruderHealth <= 0) {
				intruderDead = true;
			}
			if (health <= 0) {
				isDead = true;
			}
		}
		else {
			// check for PAINKILLERS
			if (searchInventory("PAINKILLERS")) {
				cout << "You have PAINKILLERS, do you want to take them?" << endl;
				cout << "1. Use PAINKILLERS." << endl;
				cout << "2. Save them." << endl;
				cout << endl;

				cout << "Enter your selection: ";
				choice = getValidInt(1, 2);

				cout << endl;

				if (choice == 1) {
					cout << "You swallow the PAINKILLERS. That should hold you "
						<< "for a while.\n" << endl;
					health += 25;
				}
			}

			printStatus();

			// create menu and add options
			Menu battleMenu;
			battleMenu.addOption("Keep fighting the INTRUDER");
			battleMenu.addOption("Run back to the LIVING ROOM");

			cout << "\n+" << string(50, '-') << "+" << endl;
			cout << "What would you like to do?\n" << endl;
			battleMenu.printMenu();
			cout << "+" << string(50, '-') << "+\n" << endl;

			cout << "Enter your selection: ";
			choice = getValidInt(1, battleMenu.getMenuSize());
			cout << endl;
		}

	} while (!intruderDead && !isDead && choice != 2);

	if (intruderDead) {
		cout << "The INTRUDER is down!\n" << endl;
		cout << "You notice a key has fallen from their pocket. You grab it.\n" << endl;

		attic->setObtainedSpecial(true);

		//check inventory size
		if (inventory.size() == MAX_INVENTORY) {
			cout << "...But your Inventory is full.\n" << endl;
		}
		else {
			inventory.push_back("BASEMENT-KEY");
			cout << "ITEM OBTAINED: BASEMENT-KEY\n" << endl;
			cout << "Now you can escape!\n" << endl;
		}
	}
}

/*
** Search function for the LivingRoom. There are various items and dangers
** depending on where the user looks.
*******************************************************************************/
void Game::searchLivingRoom() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	do {
		printStatus();

		// create menu and add options
		Menu searchLivingRoomMenu;
		searchLivingRoomMenu.addOption("Check behind the couch");
		searchLivingRoomMenu.addOption("Check under the stack of pizza boxes");
		searchLivingRoomMenu.addOption("Check behind the curtains");
		searchLivingRoomMenu.addOption("Back to room menu");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "Where would you like to search?\n" << endl;
		searchLivingRoomMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, searchLivingRoomMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			cout << "You check behind the couch..." << endl;

			// if not seen before
			if (!searchDiscardPile("EVICTION-NOTICE") && !searchInventory("EVICTION-NOTICE")) {
				cout << "You find a crumpled note.\n" << endl;

				// verify inventory
				if (inventory.size() == MAX_INVENTORY) {
					cout << "...But your Inventory is full." << endl;
				}
				else {
					cout << "You read the note:\n" << endl
						<< "\"EVICTION NOTICE\n" << endl
						<< "Due to your delinquent payments and failure to "
						<< "maintain this property per your contract agreement,"
						<< "\nyou are to be evicted from the premises. Boarded "
						<< "windows and doors will not help you. Please remove "
						<< "them.\"" << endl;

					cout << "\nYou recall why you drank your night away. You "
						<< "laugh and think of the BASEMENT window. The only "
						<< "way in or out.\n";

					inventory.push_back("EVICTION-NOTICE");
					cout << "ITEM OBTAINED: EVICTION-NOTICE\n" << endl;
				}
			}
			else {
				cout << "You've already looked here!\n" << endl;
			}
				
		}
		else if (choice == 2) {
			cout << "You find nothing of value.\n" << endl;
		}			
		else if (choice == 3) {
			cout << "You check behind the curtains..." << endl;
			cout << "Not much here but boarded-up windows.\n" << endl;
		}
	} while (choice != 4);
}

/*
** Search function for the Bedroom. There are various items and dangers
** depending on where the user looks.
*******************************************************************************/
void Game::searchBedroom() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	do {
		printStatus();

		// create menu and add options
		Menu searchBedroomMenu;
		searchBedroomMenu.addOption("Check under the bed");
		searchBedroomMenu.addOption("Check the closet");
		searchBedroomMenu.addOption("Check behind the pile of laundry");
		searchBedroomMenu.addOption("Back to room menu");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "Where would you like to search?\n" << endl;
		searchBedroomMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, searchBedroomMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			//printStatus();
			cout << "You check under the bed...\n"
				<< "Gross. Shouldn't have looked.\n" << endl;
		}
		else if (choice == 2) {
			cout << "You check the closet..." << endl;
			cout << "A rat scurries out and bites your foot!\n" << endl;
			health -= 10;

			// if rat kills user, end game
			if (health <= 0) {
				isDead = true;
				choice = 4;
			}
		}
		else if (choice == 3) {
			cout << "You check behind the pile of laundry..." << endl;

			// if not seen before
			if (!bedroom->getPainkillersFound()) {
				cout << "You find PAINKILLERS!\n" << endl;

				// check inventory size
				if (inventory.size() == MAX_INVENTORY) {
					cout << "...But your Inventory is full." << endl;
				}
				else {
					inventory.push_back("PAINKILLERS");
					cout << "ITEM OBTAINED: PAINKILLERS\n" << endl;
					bedroom->setPainkillersFound(true);
				}
			}
			else {
				cout << "You've already looked here!\n" << endl;
			}
		}
	} while (choice != 4);
}

/*
** Search function for the Kitchen. There are various items and dangers depending
** on where the user looks.
*******************************************************************************/
void Game::searchKitchen() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	do {
		printStatus();

		// create menu and add options
		Menu searchKitchenMenu;
		searchKitchenMenu.addOption("Check the sink");
		searchKitchenMenu.addOption("Check the fridge");
		searchKitchenMenu.addOption("Check the cabinets");
		searchKitchenMenu.addOption("Back to room menu");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "Where would you like to search?\n" << endl;
		searchKitchenMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, searchKitchenMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			cout << "You check the sink..." << endl;

			// if not seen before
			if (!searchDiscardPile("CERAMIC-PLATE") && !searchInventory("CERAMIC-PLATE")) {
				cout << "You found a CERAMIC-PLATE!\n" << endl;

				// check inventory size
				if (inventory.size() == MAX_INVENTORY) {
					cout << "...But your Inventory is full." << endl;
				}
				else {
					inventory.push_back("CERAMIC-PLATE");
					cout << "ITEM OBTAINED: CERAMIC-PLATE\n" << endl;
				}
			}
			else {
				cout << "You've already looked here!\n" << endl;
			}
		}
		else if (choice == 2) {
			//printStatus();
			cout << "You check the fridge..." << endl;

			// if not seen before
			if (!kitchen->getPainkillersFound()) {
				cout << "You find PAINKILLERS!\n" << endl;

				// check inventory size
				if (inventory.size() == MAX_INVENTORY) {
					cout << "...But your Inventory is full." << endl;
				}
				else {
					inventory.push_back("PAINKILLERS");
					cout << "ITEM OBTAINED: PAINKILLERS\n" << endl;
					kitchen->setPainkillersFound(true);
				}
			}
			else {
				cout << "You've already looked here!\n" << endl;
			}
		}
		else if (choice == 3) {
			cout << "You check the cabinets..." << endl;
			cout << "There's a hornet's nest inside! You quickly shut the door.\n" << endl;
		}
	} while (choice != 4);
}

/*
** Search function for the Pantry. There are various items and dangers
** depending on where the user looks.
*******************************************************************************/
void Game::searchPantry() {
	using std::cout;
	using std::endl;
	using std::string;

	int choice = 0;

	do {
		printStatus();

		// create menu and add options
		Menu searchPantryMenu;
		searchPantryMenu.addOption("Check the shelves on the left");
		searchPantryMenu.addOption("Check the shelves on the right");
		searchPantryMenu.addOption("Check the basket in the corner");
		searchPantryMenu.addOption("Back to room menu");

		cout << "\n+" << string(50, '-') << "+" << endl;
		cout << "Where would you like to search?\n" << endl;
		searchPantryMenu.printMenu();
		cout << "+" << string(50, '-') << "+\n" << endl;

		cout << "Enter your selection: ";
		choice = getValidInt(1, searchPantryMenu.getMenuSize());
		cout << endl;

		if (choice == 1) {
			cout << "You check the shelves on the left...\n"
				<< "Nothing but packets of ramen noodles.\n" << endl;
			
		}
		else if (choice == 2) {
			cout << "You check the shelves on the right..." << endl;

			// if not seen before
			if (!searchDiscardPile("PLASTIC-SPORK") && !searchInventory("PLASTIC-SPORK")) {
				cout << "You spot a PLASTIC-SPORK. Not very useful, but who knows?\n" << endl;

				//check inventory size
				if (inventory.size() == MAX_INVENTORY) {
					cout << "...But your Inventory is full." << endl;
				}
				else {
					inventory.push_back("PLASTIC-SPORK");
					cout << "ITEM OBTAINED: PLASTIC-SPORK\n" << endl;
				}
			}
			else {
				cout << "You've already looked here!\n" << endl;
			}
		}
		else if (choice == 3) {
			cout << "You check the basket in the corner...\n"
				<< "A snake bites your hand!\n" << endl;
			health -= 10;

			// if snake kills you, end the game
			if (health <= 0) {
				isDead = true;
				choice = 4;
			}
		}
	} while (choice != 4);
}

/*
** Search function for the Attic. This allows the user to pick up the BASEMENT-KEY
** if not already done.
*******************************************************************************/
void Game::searchAttic() {
	using std::cout;
	using std::endl;

	// if BASEMENT-KEY was already obtained, notify the user
	if (searchInventory("BASEMENT-KEY")) {
		cout << "There's nothing here but the INTRUDER's body." << endl;
	}
	else {
		if (inventory.size() == MAX_INVENTORY) {
			cout << "That BASEMENT-KEY is needed for your escape, but your "
				<< "inventory is full!" << endl;
		}
		else {
			cout << "You grab the BASEMENT-KEY from where it dropped.\n" << endl;
			inventory.push_back("BASEMENT-KEY");
			cout << "ITEM OBTAINED: BASEMENT-KEY\n" << endl;
		}
	}
}

/*
** Searches the user's Inventory for a specified item.
**
** @param string  Item to be searched for.
*******************************************************************************/
bool Game::searchInventory(std::string item) {
	for (std::list<std::string>::iterator i = inventory.begin();
		i != inventory.end(); ++i) {

		if (*i == item) {
			return true;
		}
	}

	return false;
}

/*
** Searches the user's discarded items for a specified item. Used to see if an item
** was already discovered.
**
** @param string  Item to be searched for.
*******************************************************************************/
bool Game::searchDiscardPile(std::string item) {
	for (std::list<std::string>::iterator i = discardedItems.begin();
		i != discardedItems.end(); ++i) {

		if (*i == item) {
			return true;
		}
	}

	return false;
}

/*
** Allows for the user to discard a listed item from their Inventory, but checks
** to see if item is necessary first.
*******************************************************************************/
void Game::removeItem() {
	using std::cout;
	using std::endl;

	int choice = 0;
	int count = 1;

	printStatus();

	//display inventory
	cout << endl;
	cout << "Which item would you like to remove?" << endl;
	for (std::list<std::string>::iterator i = inventory.begin();
		i != inventory.end(); ++i) {

		cout << count << ". " << *i << endl;
		count++;
	}

	cout << count << ". Go back.\n" << endl;

	// prompt user which item to remove
	cout << "Enter your selection: ";
	choice = getValidInt(1, count+1);

	if (choice < count) {
		int secondCount = 0;
		int value = choice - 1;
		std::string item;

		// find item
		for (std::list<std::string>::iterator i = inventory.begin();
			i != inventory.end(); ++i) {

			if (secondCount == value) {
				item = *i;
			}

			secondCount++;
		}

		cout << endl;

		// make sure item isn't required
		if (item == "FLASHLIGHT") {
			cout << "You need this to see.\n" << endl;
		}
		else if (item == "DEAD-FLASHLIGHT") {
			cout << "You just need to find some batteries for this.\n" << endl;
		}
		else if (item == "PANTRY-KEY") {
			cout << "This could unlock something useful." << endl;
		}
		else if (item == "TRASHCAN-LID" || item == "KNIFE") {
			cout << "You'll need this for protection.\n" << endl;
		}
		else if (item == "BASEMENT-KEY") {
			cout << "There's only one way out. You need this.\n" << endl;
		}	
		else {
			inventory.remove(item); 
			discardedItems.push_back(item); 
			cout << "You have removed: " << item << endl << endl;
		}	
	}
}

/*
** Prints text if user wins game.
*******************************************************************************/
void Game::winScreen() {
	using std::cout;
	using std::endl;

	printStatus();

	cout << "\nWhat a crazy night! You've got to get out of here before "
		<< "the cops show up.\n" << endl
		<< "THE END" << endl;

	std::cout << "Press ENTER to close program..." << std::flush;
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

/*
** Prints text if user loses game.
*******************************************************************************/
void Game::loseScreen() {
	using std::cout;
	using std::endl;

	printStatus();

	cout << "Looks like you weren't able to escape. Too bad.\n" << endl;

	std::cout << "Press ENTER to close program..." << std::flush;
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

/*
** Prints user's current health and inventory.
*******************************************************************************/
void Game::printStatus() {
	using std::cout;
	using std::endl;

	// print health and inventory
	cout << "HEALTH: " << health << endl;
	cout << "INVENTORY: ";
	for (std::list<std::string>::iterator i = inventory.begin();
		i != inventory.end(); ++i) {
		cout << *i << "  ";
	}

	cout << endl;
}