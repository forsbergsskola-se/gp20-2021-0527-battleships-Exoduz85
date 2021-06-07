#pragma once
#include "Ship.h"

enum class State{ Empty, Occupied, Miss, Hit, Attacked };

class Cell{
public:
	Ship* ship;
	State state;
	Cell() = default;
	State checkCell(){
		if(state == State::Hit || state == State::Miss){
			state = State::Attacked;
		}
		if(state == State::Occupied){
			state = State::Hit;
		}
		if(state == State::Empty){
			state = State::Miss;
		}
		return state;
	}
};