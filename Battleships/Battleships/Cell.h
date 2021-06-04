#pragma once
#include <iostream>
#include "Ship.h"

class Cell{
private:
	Ship ship;
public:
	Cell() = default;
	void setCell(Ship ship){
		this->ship = ship;
	}
	Ship getCell(){
		return this->ship;
	}
};