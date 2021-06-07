#pragma once
#include "Ship.h"

enum class State{ Empty, Occupied, Miss, Hit };

class Cell{
public:
	Ship* ship;
	State state;
	Cell() = default;
	State checkCell(bool attacking){
		if(state == State::Occupied){
			if(attacking){ state = State::Hit; }
		}
		if(state == State::Empty){
			if(attacking){ state = State::Miss; }
		}
		return state;
	}
};

// each cell has it's "own" ship right now but needs to be "one" ship and not an own, 
// create a pointer to that ship instead of an instance for each cell?