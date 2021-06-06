#pragma once
#include <string>

class Ship{
	int length = 0;
	int health = 0;
public:
	bool verticalSet = false;
	std::string name;
	Ship() = default;
	Ship(std::string n, int l, int h){
		this->name = n;
		this->length = l;
		this->health = h;
	}
	void setLength(int newLength){
		this->length = newLength;
	}
	int getLength(){
		return this->length;
	}
	void setHealth(){
		this->health--;
	}
	int getHealth(){
		return this->health;
	}
};