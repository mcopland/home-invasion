/*******************************************************************************
** Program: homeInvasion
** File:    LivingRoom.hpp
** -----------------------------------------------------------------------------
** This is the LivingRoom class specification (header) file. LivingRoom is
** derived from the Space class.
*******************************************************************************/

#ifndef LIVINGROOM_HPP
#define LIVINGROOM_HPP

#include "Space.hpp"

class LivingRoom : public Space {
public:
	LivingRoom(std::string value) : Space(value) {};
	char spaceMenu();
	void spaceIntro();
};

#endif