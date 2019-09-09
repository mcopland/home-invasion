/*******************************************************************************
** Program: homeInvasion
** File:    Space.cpp
** -----------------------------------------------------------------------------
** This is the Space class function implementation file. Space is a virtual
** parent class that lays the foundation for six derived classes.
*******************************************************************************/

#include "Space.hpp"

/*
** Constructor for Space class. Sets the location name and initializes values.
**
** @param string  Name to be set.
*******************************************************************************/
Space::Space(std::string name) {
	// set room names
	if (name == "LIVING ROOM")
		this->spaceName = name;
	else if (name == "BEDROOM")
		this->spaceName = name;
	else if (name == "KITCHEN")
		this->spaceName = name;
	else if (name == "PANTRY")
		this->spaceName = name;
	else if (name == "BASEMENT")
		this->spaceName = name;
	else if (name == "ATTIC")
		this->spaceName = name;

	// initialize pointers
	this->ptrNorth = nullptr;
	this->ptrSouth = nullptr;
	this->ptrEast = nullptr;
	this->ptrWest = nullptr;

	// initialize boolean values
	this->lightsOn = false;
	this->obtainedSpecial = false;
	this->obtainedRequired = false;
	this->painkillersFound = false;
	this->pantryUnlocked = false;
}

/*
** Sets pointers for each Space based on the current Space object occupied.
**
** @param char    Direction of pointer that will be set.
** @param Space*  Room that will be linked to pointer.
*******************************************************************************/
void Space::setPointer(char direction, Space* location) {
	if (direction == 'N')
		this->ptrNorth = location;
	else if (direction == 'S')
		this->ptrSouth = location;
	else if (direction == 'E')
		this->ptrEast = location;
	else if (direction == 'W')
		this->ptrWest = location;
}

/*
** Getters (accessors) for Space class.
*******************************************************************************/
Space* Space::getNorth() {
	return ptrNorth;
};

Space* Space::getSouth() {
	return ptrSouth;
};

Space* Space::getEast() {
	return ptrEast;
};

Space* Space::getWest() {
	return ptrWest;
};

std::string Space::getName() {
	return spaceName;
};

bool Space::getObtainedSpecial() {
	return obtainedSpecial;
};

bool Space::getPainkillersFound() {
	return painkillersFound;
};

bool Space::getPantryUnlocked() {
	return pantryUnlocked;
};

/*
** Setters (mutators) for Space class.
*******************************************************************************/
void Space::setLightsOn(bool val) {
	this->lightsOn = val;
};

void Space::setObtainedRequired(bool val) {
	this->obtainedRequired = val;
};

void Space::setObtainedSpecial(bool val) {
	this->obtainedSpecial = val;
};

void Space::setPainkillersFound(bool val) {
	this->painkillersFound = val;
};

void Space::setPantryUnlocked(bool val) {
	this->pantryUnlocked = val;
};