#pragma once
#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <tuple>
#include "Cell.h"
#include "Fleet.h"

struct{
	int dx;
	int dy;
} directions[] = {{0, 0, }, {-1, 0, }, {0, -1}, {0, 1},  {1, 0}};

class Battlefield{
private:
	static const int x = 10;
	static const int y = 10;
	Cell Grid[x][y]{};
	char Boarder[x][y]{{'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'}, {'E', '4'}, {'F', '5'}, {'G', '6'}, {'H', '7'}, {'I', '8'}, {'J', '9'}};
public:
	void printBattlefield(){ // now should instead print out hits and misses.
		std::cout << "_________________________________\n| ";
		for (auto& k : Boarder){
			std::cout << "  " << k[1];
		}
		std::cout << "|\n";
		for (int i = 0; i < x; i++){
			std::cout << "|" << Boarder[i][0];
			for(int j = 0; j < y; j++){
				if(Grid[i][j].state == State::Occupied) std::cout << "  S";
				else std::cout << "  *";
			}
			std::cout << "|\n";
		}
		int set = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wstring s = L"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾";
		std::wcout << s << std::endl << std::flush;
		set = _setmode(_fileno(stdout), _O_TEXT);
	}
	bool setShip(Ship ship, std::string pos){
		std::tuple<int, int> index = getIndex(pos);
		if(checkSurroundingCells(std::get<0>(index), std::get<1>(index), ship)){
			return false;
		}
		for(int i = 0; i < ship.getLength(); i++){
			int x = std::get<0>(index);
			int y = std::get<1>(index);
			if(ship.verticalSet){
				x = x + i;
			}else{
				y = y + i;
			}
			Grid[x][y].ship = ship;
			Grid[x][y].state = State::Occupied;
		} 
		return true;
	}
	std::tuple<int, int> getIndex(std::string pos){
		int index1 = 0;
		int index2 = 0;
		for(int i = 0; i < x; i++){
			if(Boarder[i][0] == std::toupper(pos[0])) index1 = i;
			for(int j = 0; j < y; j++){
				if(Boarder[j][1] == pos[1]) index2 = j;
			}
		}
		return std::tuple<int, int>{index1, index2};
	}
	bool checkSurroundingCells(int index1, int index2, Ship ship){
		if(ship.getLength() + index1 > 10 && ship.verticalSet){
			std::cout << "Ship was too long to fit!" << std::endl;
			return true;
		}
		if(ship.getLength() + index2 > 10 && !ship.verticalSet){
			std::cout << "Ship was too long to fit!" << std::endl;
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
		int index1 = rand() % 9;
		int index2 = rand() % 9;
		for(int i = 0; i < 5; i++){
			auto ship = fleet.getFleet()[i];
			ship.verticalSet = index1 % 2 == 0 ? true : false;
			while(checkSurroundingCells(index1, index2, ship)){
				index1 = rand() % 9;
				index2 = rand() % 9;
			}
			for(int j = 0; j < ship.getLength(); j++){
				int x = index1;
				int y = index2;
				if(ship.verticalSet){
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
	bool attack(std::string pos){
		std::tuple<int, int> index = getIndex(pos);
		State state = Grid[std::get<0>(index)][std::get<1>(index)].checkCell(true);
		if(state == State::Hit){
			Grid[std::get<0>(index)][std::get<1>(index)].ship.setHealth();
			if(Grid[std::get<0>(index)][std::get<1>(index)].ship.getHealth() <= 0){
				// ship dead
				std::cout << Grid[std::get<0>(index)][std::get<1>(index)].ship.name << " destroyed!\nExcellent work..\n";
			}
			return true;
		}
		return false;
	}
};
