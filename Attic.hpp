/*******************************************************************************
** Program: homeInvasion
** File:    Attic.hpp
** -----------------------------------------------------------------------------
** This is the Attic class specification (header) file. Attic is derived from
** the Space class.
*******************************************************************************/

#ifndef ATTIC_HPP
#define ATTIC_HPP

#include "Space.hpp"

class Attic : public Space {
public:
	Attic(std::string value) : Space(value) {};
	char spaceMenu();
	void spaceIntro();
};

#endif