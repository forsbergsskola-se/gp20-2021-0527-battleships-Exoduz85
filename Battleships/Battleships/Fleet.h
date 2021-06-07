#pragma once
#include <vector>
#include "Ship.h"

class Fleet{
private:
	std::vector<Ship*> fleet;
	std::string ships[5] = {"Patrol Boat", "Submarine", "Cruiser", "Destroyer", "Carrier"};
	int maxSize = 5;
public:
	void setUpShips(){
		for(int i = 0; i < maxSize; i++){
			int size = i + 1;
			if(i == 0) size++;
			Ship* ship = new Ship(ships[i], size, i + 1);
			fleet.push_back(ship);
		}
	}
	std::vector<Ship*> getFleet(){
		return this->fleet;
	}
};