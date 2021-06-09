#pragma once
#include <iostream>
#include "Battlefield.h"
#include "Player.h"
using namespace std;

Player playerOne;
Player playerTwo;


class Game{
public:
	bool playerOneTurn = true;
	bool running = true;
	string posToAttack;
	void start(){
		while (running){
			switch(playerOneTurn){
				case true:
					std::cout << "Player one turn.\n\n";
					if(playerOne.playerInitialized){
						std::cout << "Displaying your opponents battlefield(H = hit, *= miss, ? = Unknown)\n\n";
						playerTwo.battlefield.printBattlefield(false);
						playerOne.battlefield.printBattlefield(true);
						while(true){
							cout << "Select a cell to bomb: (e.g: f5)\n";
							cin >> posToAttack;
							auto index = playerOne.battlefield.getIndex(posToAttack);
							if(get<0>(index) < 0 || get<0>(index) > 9 ||
								get<1>(index) < 0 || get<1>(index) > 9){
								cout << "Incorrect position, please try again!\n";
								continue;
							}
							break;
						}
						system("CLS");
						if(!playerOne.attack(playerTwo, posToAttack)){
							cout << "Try Again!\n";
							continue;
						}
						if(!playerTwo.hasShips()){
							cout << "Yippey, you've sunk all your opponents ships, PLAYER ONE WON!!! :)\n";
							quit();
						}
						playerOneTurn = false;
					} else{
						if(!playerOne.setUpPlayer()) continue;
						playerOneTurn = false;
					}
					break;
				default:
					std::cout << "Player two turn.\n\n";
					if(playerTwo.playerInitialized){
						std::cout << "Displaying your opponents battlefield(H = hit, *= miss, ? = Unknown)\n\n";
						playerOne.battlefield.printBattlefield(false);
						playerTwo.battlefield.printBattlefield(true);
						while(true){
							cout << "Select a cell to bomb: (e.g: f5)\n";
							cin >> posToAttack;
							auto index = playerTwo.battlefield.getIndex(posToAttack);
							if(get<0>(index) < 0 || get<0>(index) > 9 ||
								get<1>(index) < 0 || get<1>(index) > 9){
								cout << "Incorrect position, please try again!\n";
								continue;
							}
							break;
						}
						system("CLS"); // need to redo so that the player can continue to attack
						if(!playerTwo.attack(playerOne, posToAttack)){
							cout << "Try Again!\n";
							continue;
						}
						if(!playerOne.hasShips()){
							cout << "Yippey, you've sunk all your opponents ships, PLAYER TWO WON!!! :)\n";
							quit();
						}
						playerOneTurn = true;
					} else{
						if(!playerTwo.setUpPlayer()) continue;
						playerOneTurn = true;
					}
					break;
			}
		}
	}
	void quit(){
		running = false;
	}
};