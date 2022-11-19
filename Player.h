#pragma once
#include <iostream>
#include "Coordinates.h"
#include "GameObject.h"

//класс игрока, общается с остальными компонентами с помощью координат.

class Player
{
private:
	Coordinates coordinates;
	Coordinates minCoordinates;
	Coordinates maxCoordinates;
	int HP = 100;
	int lengthStep = 1;
public:
	Player(Coordinates coord, Coordinates minCoord, Coordinates maxCoord)
	{
		coordinates = coord;
		minCoordinates = minCoord;
		maxCoordinates = maxCoord;

	}
	void StepUp()
	{
		if (maxCoordinates.y > coordinates.y + 1)
			coordinates.y += lengthStep;
	}
	void StepDown() 
	{
		if (minCoordinates.y < coordinates.y - 1)
			coordinates.y -= lengthStep;
	}
	void StepLeft()
	{
		if (minCoordinates.x < coordinates.x - 1)
			coordinates.x -= lengthStep;
	}

	void StepRight()
	{
		if (maxCoordinates.x > coordinates.x + 1)
			coordinates.x += lengthStep;
	}
	void SetCoordinate(int x, int y)
	{
		coordinates.x = x;
		coordinates.y = y;
	}
	Coordinates GetCoord()
	{
		return coordinates;
	}
};

