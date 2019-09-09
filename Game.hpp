/*******************************************************************************
** Program: homeInvasion
** File:    Game.hpp
** -----------------------------------------------------------------------------
** This is the Game class specification (header) file. The Game class manages
** the gameplay rules and logic while tracking the user's characteristics.
*******************************************************************************/

#ifndef GAME_HPP 
#define GAME_HPP

// rooms
#include "Attic.hpp"
#include "Basement.hpp"
#include "Bedroom.hpp"
#include "Kitchen.hpp"
#include "LivingRoom.hpp"
#include "Pantry.hpp"

#include <ctime>
#include <list>

class Game {
private:
	// rooms
	Space* attic;
	Space* basement;
	Space* bedroom;
	Space* kitchen;
	Space* livingRoom;
	Space* pantry;
	
	// user and game characteristics
	Space* location;
	bool isDead;
	bool gameWon;
	const int MAX_INVENTORY = 6;
	int health;
	int threatLevel;
	std::list<std::string> discardedItems;
	std::list<std::string> inventory;
public:
	Game();
	void play();

	// special room
	void specialAttic();
	void specialBasement();
	void specialBedroom();
	void specialKitchen();
	void specialLivingRoom();
	void specialPantry();
	
	// search room
	void searchAttic();
	void searchBedroom();
	void searchKitchen();
	void searchLivingRoom();
	void searchPantry();
	
	// inventory management
	bool searchDiscardPile(std::string);
	bool searchInventory(std::string);
	void removeItem();
	
	// other
	void printStatus();
	void loseScreen();
	void winScreen();
};

#endif