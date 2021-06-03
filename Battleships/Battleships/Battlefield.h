#pragma once
#include <iostream>

struct Size{
	int x;
	int y;
	Size(int x, int y) : x(x), y(y){};
};
class Battlefield{
	const int x = 10;
	const int y = 10;
	Size size = *new Size(x, y);
public:
	void testPrintSize(){
		std::cout << size.x << std::endl;
		std::cout << size.y << std::endl;
	}
};