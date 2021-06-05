#pragma once
#include <vector>
#include "Ship.h"

class Fleet{
private:
	std::vector<Ship> fleet;
	std::string ships[5] = {"Patrol Boat", "Submarine", "Cruiser", "Destroyer", "Carrier"};
	int maxSize = 5;
public:
	void setUpShips(){
		for(int i = 0; i < maxSize; i++){
			Ship ship = Ship(ships[i], i + 1);
			fleet.push_back(ship);
		}
	}
	std::vector<Ship> getFleet() const{
		return this->fleet;
	}
	Ship getShip(std::string shipName){
		for(auto ship : fleet){
			if(ship.name == shipName){
				return ship;
			}
		}
		return Ship("notFound", 0);
	}
};
