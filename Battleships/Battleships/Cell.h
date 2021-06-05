#pragma once
#include "Ship.h"

class Cell{
private:
	Ship ship;
public:
	Cell() = default;
	void setCell(Ship s){ // works as intended..
		ship = s;
	}
	Ship getCell(){ // WHY THE HELL IS THIS RETURNING A DEFAULT SHIP?????????? DOES NOT WORK AS INTENDED!
		std::cout << "From cell class: " << ship.name << " length: " << ship.getLength() << std::endl;
		return ship;
	}
};