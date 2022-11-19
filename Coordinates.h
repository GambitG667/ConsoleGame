#pragma once
#include <iostream>


class Coordinates
{
public:
	int x, y;

	Coordinates()
	{
		x = 0;
		y = 0;
	}

	Coordinates(int xCoord, int yCoord)
	{
		x = xCoord;
		y = yCoord;
	}
};
