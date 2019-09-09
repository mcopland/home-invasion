/*******************************************************************************
** Program: homeInvasion
** File:    Bedroom.hpp
** -----------------------------------------------------------------------------
** This is the Bedroom class specification (header) file. Bedroom is derived
** from the Space class.
*******************************************************************************/

#ifndef BEDROOM_HPP
#define BEDROOM_HPP

#include "Space.hpp"

class Bedroom : public Space {
public:
	Bedroom(std::string value) : Space(value) {};
	char spaceMenu();
	void spaceIntro();
};

#endif