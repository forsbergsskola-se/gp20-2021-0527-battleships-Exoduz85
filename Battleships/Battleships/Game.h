#pragma once
#include <iostream>
#include "Battlefield.h"
#include "Fleet.h"
#include "Ship.h"

using namespace std;
std::string ships[5] = {"Patrol Boat", "Submarine", "Cruiser", "Destroyer", "Carrier"};
Fleet fleet;
Battlefield battlefield;

class Game{
private:
	Position positionToBomb;
public:
	bool running = true;
	void start(){
		fleet.setUpShips();
		Ship ship = fleet.getShip(ships[1]);
		string test = "b2";
		battlefield.setShip(ship, test);
		battlefield.checkCell("b2");
		battlefield.checkCell("c3");
		running = true;
		cout << endl;
		battlefield.printBattlefield();
		cout << "Please select a position to bomb: (e.g: b2 or g8)";
		string toBomb;
		cin >> toBomb;
		// now add check for hit ( but where? in battlefield.h? or? )
	}
	void quit(){
		running = false;
	}
};