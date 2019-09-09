/*******************************************************************************
** Program: homeInvasion
** File:    Kitchen.hpp
** -----------------------------------------------------------------------------
** This is the Kitchen class specification (header) file.  Kitchen is derived
** from the Space class.
*******************************************************************************/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "Space.hpp"

class Kitchen : public Space {
public:
	Kitchen(std::string value) : Space(value) {};
	char spaceMenu();
	void spaceIntro();
};

#endif