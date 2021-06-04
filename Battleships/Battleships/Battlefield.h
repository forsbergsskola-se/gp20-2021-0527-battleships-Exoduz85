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
} directions[] = {{-1, -1, }, {-1, 0, }, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

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
    bool occupiedCell(int index1, int index2){
		Ship ship = Grid[index1][index2].getCell();
		if(ship.getLength() == 0) return false; // no ship 
		return true; // yes ship
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
	void addFleetToGrid(Fleet fleet){ // still puts ships on positions where ships already are present!
		int index1 = rand() % 9;
		int index2 = rand() % 9;
		for (int i = 0; i < 5; i++){
			auto ship = fleet.getFleet()[i];
			while(checkSurroundingCells(index1, index2, ship.getLength())){
				index1 = rand() % 9;
				index2 = rand() % 9;
			}
			// for future ref, vertical or horizontal position for ship?
			// Grid[index1][index2 + i].setCell(ship); horizontal |or| Grid[index1 + i][index2].setCell(ship); vertical (rnd bool for this?)
			for(int i = 0; i < ship.getLength(); i++){
				Grid[index1][index2 + i].setCell(ship);
				int z = index2 + i;
				std::cout << ship.name << " set in position: (" << index1 << ", " << z << ")" << std::endl;
			}
		}
	}
	bool checkSurroundingCells(int index1, int index2, int shipLength){
		for (auto& direction : directions){
			int x = index1 + direction.dx;
			int y = index2 + direction.dy;
			if(shipLength + y > 9) return false;
			if(x < 0 || y < 0) continue;
			if(occupiedCell(x, y)) return true; // ship next to cell
		}
		return false; // no ship next to cell
	}
};
