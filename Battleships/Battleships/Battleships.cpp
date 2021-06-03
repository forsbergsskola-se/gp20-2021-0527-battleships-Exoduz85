#include <iostream>
#include "Fleet.h"
using namespace std;
const char * ships[5]{"Patrol Boat", "Submarine", "Cruiser", "Destroyer", "Carrier"};

int x = 10;
int y = 10;

Fleet fleet;

int main()
{
	fleet.setUpShips();
	cout << fleet.getShip(ships[0]).name << " size: " << fleet.getShip(ships[0]).getLength() << endl;
	cout << fleet.getShip(ships[1]).name << " size: " << fleet.getShip(ships[1]).getLength() << endl;
	cout << fleet.getShip(ships[2]).name << " size: " << fleet.getShip(ships[2]).getLength() << endl;
	cout << fleet.getShip(ships[3]).name << " size: " << fleet.getShip(ships[3]).getLength() << endl;
	cout << fleet.getShip(ships[4]).name << " size: " << fleet.getShip(ships[4]).getLength() << endl;
}