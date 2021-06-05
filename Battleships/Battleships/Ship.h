#pragma once
#include <string>
#include <vector>
#include "Position.h"

class Ship{
protected:
	int length = 0;
	std::vector<Position> shipPos;
public:
	Ship() = default;
	std::string name = "";
	Ship(std::string n, int l){
		this->name = n;
		this->length = l;
	}
	void setLength(int newLength){
		this->length = newLength;
	}
	int getLength(){
		return this->length;
	}
	void setPosition(const Position position){
		shipPos.push_back(position);
	}
	std::vector<Position> getPosition() const{
		return this->shipPos;
	}
	bool validAsShip(){
		if(this->getLength() < 1) return false;
		return true;
	}
};