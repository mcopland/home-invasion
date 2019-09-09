/*******************************************************************************
** Program: homeInvasion
** File:    Basement.hpp
** -----------------------------------------------------------------------------
** This is the Basement class specification (header) file. Basement is derived
** from the Space class.
*******************************************************************************/

#ifndef BASEMENT_HPP 
#define BASEMENT_HPP

#include "Space.hpp"

class Basement : public Space {
public:
	Basement(std::string value) : Space(value) {};
	char spaceMenu();
	void spaceIntro();
};

#endif