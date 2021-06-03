#include <iostream>
#include "Fleet.h"
using namespace std;
static const char * ships[5]{"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};

int x = 10;
int y = 10;

Fleet fleet;

int main()
{
	fleet.setUpShips();
	cout << fleet.getShip(ships[0]).name << endl;
	cout << fleet.getShip(ships[1]).name << endl;
	cout << fleet.getShip(ships[2]).name << endl;
	cout << fleet.getShip(ships[3]).name << endl;
	cout << fleet.getShip(ships[4]).name << endl;
}