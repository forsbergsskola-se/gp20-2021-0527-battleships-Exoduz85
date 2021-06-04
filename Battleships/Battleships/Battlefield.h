#pragma once
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include "Cell.h"

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
				if(i == 0){
					std::cout << "  " << j[1];
				}
				if(i > 0)
				{
					std::cout << "  *";
				}
			}
			std::cout << "|\n";
		}
		_setmode(_fileno(stdout), _O_U16TEXT);
		std::wstring s = L"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾";
		std::wcout << s << std::endl << std::flush;
		_setmode(_fileno(stdout), _O_TEXT);
	}
	void examineCell(char *vertical, char *horizontal){
		for (int i = 0; i < x; i++){
			for(auto& j : Grid){
				
			}
		}
	}
	void setShip(Ship ship, std::string pos){
		Grid[pos[0]][pos[1]].setCell(ship);
	}
};
