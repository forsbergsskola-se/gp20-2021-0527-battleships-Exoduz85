#pragma once
#include "Ship.h"

class Cell{
private:
	Ship ship;
public:
	Cell() = default;
	void setCell(Ship ship){
		this->ship = ship;
	}
	Ship getCell(){ // why is this returning an empty ship??????
		return this->ship;
	}
};