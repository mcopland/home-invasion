/*******************************************************************************
** Program: homeInvasion
** File:    Pantry.hpp
** -----------------------------------------------------------------------------
** This is the Pantry class specification (header) file. Pantry is derived
** from the Space class.
*******************************************************************************/

#ifndef PANTRY_HPP 
#define PANTRY_HPP

#include "Space.hpp"

class Pantry : public Space {
public:
	Pantry(std::string value) : Space(value) {};
	char spaceMenu();
	void spaceIntro();
};

#endif