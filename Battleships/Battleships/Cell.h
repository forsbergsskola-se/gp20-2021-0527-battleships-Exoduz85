#pragma once
#include <iostream>
#include "Ship.h"

class Cell{
private:
	Ship ship;
public:
	Cell() = default;
	void setCell(const Ship ship){
		this->ship = ship;
		std::cout << "Ship set to cell: " << this->ship.name << std::endl;
	}
	Ship getCell(){
		std::cout << "Cell occupied by: " << this->ship.name << std::endl;
		return this->ship;
	}
};