/*******************************************************************************
** Program: homeInvasion
** File:    Space.hpp
** -----------------------------------------------------------------------------
** This is the Space class specification (header) file. Space is a virtual
** parent class that lays the foundation for six derived classes.
*******************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "inputValidation.hpp"
#include "Menu.hpp"

class Space {
protected:
	// locations
	Space* ptrNorth;
	Space* ptrSouth;
	Space* ptrEast;
	Space* ptrWest;

	// characteristics
	std::string spaceName;
	bool lightsOn;
	bool obtainedRequired;
	bool obtainedSpecial;
	bool painkillersFound;
	bool pantryUnlocked;
public:
	// constructor
	Space(std::string name);

	// getters
	Space* getNorth();
	Space* getSouth();
	Space* getEast();
	Space* getWest();
	std::string getName();
	bool getObtainedSpecial();
	bool getPainkillersFound();
	bool getPantryUnlocked();
	
	// setters
	void setPointer(char direction, Space* location);
	void setLightsOn(bool val);
	void setObtainedSpecial(bool val);
	void setObtainedRequired(bool val);
	void setPainkillersFound(bool val);
	void setPantryUnlocked(bool val);

	// virtual functions
	virtual char spaceMenu() = 0;
	virtual void spaceIntro() = 0;
};

#endif