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
		// TODO SET UP FOR TWO PLAYERS!
		// TODO attacking..
		while (true)
		{
			switch(playerOneTurn){
				case true:
					std::cout << "Player one turn.\n";
					if(playerOne.playerInitialized){
						playerTwo.battlefield.printBattlefield();
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
						if(playerOne.attack(playerTwo, posToAttack)){
							cout << "Hit at position: (" << posToAttack[0] << ", " << posToAttack[1] << ")!\n";
						} else{ cout << "Miss\n"; }
						if(!playerTwo.hasShips()){
							cout << "Yippey, you've sunk all your opponents ships, PLAYER ONE WON!!! :)\n";
							quit();
						}
						playerOneTurn = false;
						//system("CLS");
					} else{
						playerOne.setUpPlayer();
						playerOneTurn = false;
					}
					break;
				default:
					std::cout << "Player two turn.\n";
					if(playerTwo.playerInitialized){
						playerOne.battlefield.printBattlefield();
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
						if(playerTwo.attack(playerOne, posToAttack)){
							cout << "Hit at position: (" << posToAttack[0] << ", " << posToAttack[1] << ")!\n";
						} else{ cout << "Miss\n"; }
						if(!playerOne.hasShips()){
							cout << "Yippey, you've sunk all your opponents ships, PLAYER TWO WON!!! :)\n";
							quit();
						}
						//system("CLS");
						playerOneTurn = true;
					} else{
						playerTwo.setUpPlayer();
						playerOneTurn = true;
					}
					break;
			}
		}
		cout << endl;
	}
	void quit(){
		running = false;
	}
};