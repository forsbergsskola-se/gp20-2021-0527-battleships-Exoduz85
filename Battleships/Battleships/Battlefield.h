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
} directions[] = {{0, 0, }, {-1, -1, }, {-1, 0, }, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

class Battlefield{
private:
	static const int x = 10;
	static const int y = 10;
	Cell Grid[x][y]{};
	char Boarder[x][y]{{'A', '0'}, {'B', '1'}, {'C', '2'}, {'D', '3'}, {'E', '4'}, {'F', '5'}, {'G', '6'}, {'H', '7'}, {'I', '8'}, {'J', '9'}};
public:
	void printBattlefield(){
		std::cout << "_________________________________\n";
		for (int i = 0; i < x; i++){
				std::cout << "|" << Boarder[i][0];
			for (auto& j : Boarder){
				if(i == 0) std::cout << "  " << j[1];
				if(i > 0) std::cout << "  *";
			}
			std::cout << "|\n";
		}
		int set = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wstring s = L"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾";
		std::wcout << s << std::endl << std::flush;
		set = _setmode(_fileno(stdout), _O_TEXT);
	}
	void setShip(Ship ship, std::string pos){
		std::tuple<int, int> index = getIndex(pos);
		Grid[std::get<0>(index)][std::get<1>(index)].setCell(ship);
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
	
	bool occupiedCell(int index1, int index2){  // ship seems to always be a default ship with length of 0 here! WHYYYYYYY?!?!?!?!??!!?
		return Grid[index1][index2].getCell().validAsShip(); // true = is ship, false = not a ship
	}
	void addFleetToGrid(Fleet fleet){
		int index1 = rand() % 9;
		int index2 = rand() % 9;
		for (int i = 0; i < 5; i++){
			while(checkSurroundingCells(index1, index2, fleet.getFleet()[i].getLength())){
				index1 = rand() % 9;
				index2 = rand() % 9;
			}
			// for future ref, vertical or horizontal position for ship?
			// Grid[index1][index2 + i].setCell(ship); horizontal |or| Grid[index1 + i][index2].setCell(ship); vertical (rnd bool for this?)
			for(int j = 0; j < fleet.getFleet()[i].getLength(); j++){
				Grid[index1][index2 + j].setCell(fleet.getFleet()[i]);
				const int z = index2 + j;
				std::cout << fleet.getFleet()[i].name << " set in position: (" << index1 << ", " << z << ")" << std::endl;
			}
		}
	}
	bool checkSurroundingCells(int index1, int index2, int shipLength){ // might not check current cell?
		for (auto& direction : directions){
			int x = index1 + direction.dx;
			int y = index2 + direction.dy;
			if(x < 0 || y < 0) continue;
			if(shipLength + y > 9){
				std::cout << "Ship was too long to fit!" << std::endl;
				return true;
			}
			return occupiedCell(x, y); // true = ship, false = no ship
		}
		return false; // no ship next to cell
	}
};
