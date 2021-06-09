#pragma once
#include "Battlefield.h"

class Player{
public:
	bool playerInitialized = false;
	Fleet fleet;
	Battlefield battlefield;
	int numShips = 5;
	bool setUpPlayer(){
		fleet.setUpShips();
		std::cout << "Do you want auto place ships?\n[y] yes, let the computer place them\t[n] no, i want to do it myself!\n";
		std::string answer;
		std::cin >> answer;
		if(answer == "y"){
			if(!battlefield.autoSetupFleetToGrid(fleet)){
				cout << "Auto place failed, please retry!\n";
				return false;
			}
			playerInitialized = true;
			battlefield.printBattlefield(false);
			return true;
		}
		for(int i = 0 ; i < numShips; i++){
			battlefield.printBattlefield(false);
			Ship* ship = fleet.getFleet()[i];
			while(true){
				std::cout << "Please select a position to set ship (e.g: b2 or g8): ";
				std::string pos;
				std::cin >> pos;
				std::cout << "Vertical [1] or horizontal [2] placement? \n";
				int rot;
				while(true){
					if(std::cin >> rot){
						break;
					}
					std::cout << "Not a valid choice.. select 1 or 2\n";
					std::cin >> rot;
				}
				ship->verticalSet = rot == 1 ? true : false;
				bool setShip = battlefield.setShip(ship, pos);
				if(!setShip){
					std::cout << "Not able to set ship there, try again!" << std::endl;
					continue;
				}
				//system("CLS");
				break;
			}
		}
		playerInitialized = true;
		return true;
	}
	bool attack(Player &opponent, std::string pos){
		return opponent.battlefield.attack(pos);
	}
	bool hasShips(){
		for (Ship* ship : fleet.getFleet()){
			if(ship->getHealth() > 0) return true;
		}
		return false;
	}
};

