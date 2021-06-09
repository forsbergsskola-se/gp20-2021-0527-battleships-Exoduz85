#pragma once
#include "Ship.h"

enum class State{ Empty, Occupied, Miss, Hit, Attacked };

class Cell{
public:
	Ship* ship;
	State state;
	Cell() = default;
};