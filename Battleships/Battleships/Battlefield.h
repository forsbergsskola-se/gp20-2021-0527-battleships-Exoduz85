#pragma once
#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <tuple>
#include "Cell.h"
#include "Fleet.h"
using namespace std;
struct{
	int dx;
	int dy;
} directions[] = {{0, 0}, {1, 0}, {0, -1}, {-1, 0}, {0, 1}};

class Battlefield{
private:
	static const int x = 10;
	static const int y = 10;
	Cell Grid[x][y]{};
	char Boarder[x][y]{{'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'}, {'E', '4'}, {'F', '5'}, {'G', '6'}, {'H', '7'}, {'I', '8'}, {'J', '9'}};
public:
	void printBattlefield(bool tabbed){
		if(tabbed) cout << "\t\t\t\t Your own battlefield:\n\t\t\t\t";
		cout << "_________________________________\n";
		if(tabbed) cout << "\t\t\t\t";
		cout << "| ";
		for (auto& k : Boarder){
			cout << "  " << k[1];
		}
		cout << "|\n";
		for (int i = 0; i < x; i++){
			if(tabbed) cout << "\t\t\t\t";
			cout << "|" << Boarder[i][0];
			for(int j = 0; j < y; j++){
				// TODO clean up so that each player sees a hidden battlefield.
				if(Grid[i][j].state == State::Hit) cout << "  X";
				else if(Grid[i][j].state == State::Miss) cout << "  O";
				else cout << "  ?";
			}
			cout << "|\n";
		}
		if(tabbed) cout << "\t\t\t\t";
		int set = _setmode(_fileno(stdout), _O_U16TEXT);
		wstring s = L"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾";
		wcout << s << endl << flush;
		set = _setmode(_fileno(stdout), _O_TEXT);
	}
	bool setShip(Ship* ship, string pos){
		tuple<int, int> index = getIndex(pos);
		if(checkSurroundingCells(get<0>(index), get<1>(index), *ship)){
			return false;
		}
		for(int i = 0; i < ship->getLength(); i++){
			int x = get<0>(index);
			int y = get<1>(index);
			if(ship->verticalSet){
				x = x + i;
			}else{
				y = y + i;
			}
			Grid[x][y].ship = ship;
			Grid[x][y].state = State::Occupied;
		} 
		return true;
	}
	tuple<int, int> getIndex(string pos){
		int index1 = 0;
		int index2 = 0;
		for(int i = 0; i < x; i++){
			if(Boarder[i][0] == toupper(pos[0])) index1 = i;
			for(int j = 0; j < y; j++){
				if(Boarder[j][1] == pos[1]) index2 = j;
			}
		}
		return tuple<int, int>{index1, index2};
	}
	bool checkSurroundingCells(int index1, int index2, Ship ship){
		if(ship.getLength() + index1 > 10 && ship.verticalSet){
			cout << "Ship was too long to fit!" << endl;
			return true;
		}
		if(ship.getLength() + index2 > 10 && !ship.verticalSet){
			cout << "Ship was too long to fit!" << endl;
			return true;
		}
		for(int i = ship.getLength(); i > 0; i--){
			for(auto & direction : directions){
				int x = index1 + direction.dx; // horizontal -
				int y = index2 + direction.dy; // vertical |
				if(!ship.verticalSet) y = y+i;
				else x = x+i;
				if(x > 9 || y > 9) return true;
				if(Grid[x][y].state == State::Occupied) return true;
			}
		}
		return false; // !ship
	}
	bool autoSetupFleetToGrid(Fleet fleet){
		int counter = 0;
		int index1 = rand() % 9;
		int index2 = rand() % 9;
		for(int i = 0; i < 5; i++){
			auto ship = fleet.getFleet()[i];
			ship->verticalSet = index1 % 2 == 0 ? true : false;
			while(checkSurroundingCells(index1, index2, *ship)){
				index1 = rand() % 9;
				index2 = rand() % 9;
				counter++;
				if(counter > 50){ // reset the grid somehow here..
					memset(Grid, 0, sizeof(Grid));
					return false;
				}
			}
			for(int j = 0; j < ship->getLength(); j++){
				int x = index1;
				int y = index2;
				if(ship->verticalSet){
					x = x + j;
				} else{
					y = y + j;
				}
				Grid[x][y].ship = ship;
				Grid[x][y].state = State::Occupied;
			}
		}
		return true;
	}
	bool attack(string pos){
		tuple<int, int> index = getIndex(pos);
		if(Grid[get<0>(index)][get<1>(index)].state == State::Miss || Grid[get<0>(index)][get<1>(index)].state == State::Hit){
			cout << "You have already attacked that cell.. pick another one!\n";
			return false;
		}
		if(Grid[get<0>(index)][get<1>(index)].state == State::Empty){
			Grid[get<0>(index)][get<1>(index)].state = State::Miss;
			cout << "Ouf, a total miss!\n";
			return true;
		}
		if(Grid[get<0>(index)][get<1>(index)].state == State::Occupied){
			Grid[get<0>(index)][get<1>(index)].ship->setHealth();
			Grid[get<0>(index)][get<1>(index)].state = State::Hit;
			cout << "Hit!\n";
			if(Grid[get<0>(index)][get<1>(index)].ship->getHealth() <= 0){
				cout << Grid[get<0>(index)][get<1>(index)].ship->name << " destroyed!\nExcellent work..\n";
			}
			return true;
		}
		return false;
	}
};