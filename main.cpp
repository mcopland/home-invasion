/*******************************************************************************
** Program: homeInvasion
** File:    main.cpp
** -----------------------------------------------------------------------------
** This is the homeInvasion main file. This program is a text-based game
** entitled "Home Invasion". The user navigates a house while collecting items
** in order to defeat the invader in the attic.
*******************************************************************************/

#include "Game.hpp"
#include "inputValidation.hpp"
#include "Menu.hpp"

#include <iostream>

int main() {
    using std::cout;
    using std::endl;

    // opening scene
	cout << "You wake to a loud crash coming from the attic."
		<< "\nStartled yet groggy, you rise from your couch and listen intently."
		<< "\nThe floorboards creak above you. You are not alone.\n"
		<< endl;

	Game mainGame;
    mainGame.play();

    return 0;
}