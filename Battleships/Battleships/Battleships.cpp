#include <iostream>

#include "Battlefield.h"
#include "Fleet.h"
using namespace std;
const char * ships[5]{"Patrol Boat", "Submarine", "Cruiser", "Destroyer", "Carrier"};

Fleet fleet;
Battlefield battlefield;

int main()
{
	fleet.setUpShips();
	cout << fleet.getShip(ships[0]).name << " size: " << fleet.getShip(ships[0]).getLength() << endl;
	cout << fleet.getShip(ships[1]).name << " size: " << fleet.getShip(ships[1]).getLength() << endl;
	cout << fleet.getShip(ships[2]).name << " size: " << fleet.getShip(ships[2]).getLength() << endl;
	cout << fleet.getShip(ships[3]).name << " size: " << fleet.getShip(ships[3]).getLength() << endl;
	cout << fleet.getShip(ships[4]).name << " size: " << fleet.getShip(ships[4]).getLength() << endl;
	cout << endl;
	battlefield.testPrintSize();
}