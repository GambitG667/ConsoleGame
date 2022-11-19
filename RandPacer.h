#pragma once
#include <iostream>
#include <string>
#include <minmax.h>
#include "Coordinates.h"
#include "GameObject.h"

//класс рандомного шагателя который генерирует комнаты.

class Pacer;
class RandPaser;
class StateOfPacer;
class UpStateOfPacer;
class DownStateOfPacer;
class LeftStateOfPacer;
class RightStateOfPacer;

class StateOfPacer
{
private:
	std::string name;
public:
	StateOfPacer(const std::string& name)
		: name(name) {}
	std::string GetName()
	{
		return name;
	}
	virtual void Step(Pacer*) = 0;
	virtual void TurnLeft(Pacer*) = 0;
	virtual void TurnRight(Pacer*) = 0;
	virtual void StepBac(Pacer* paser) = 0;
};

class Pacer
{

private:
	StateOfPacer* state;
public:	
	Coordinates coordinates;
	Coordinates maxCoordinates;
	Coordinates minCoordinates;
	int lengthJamp;

	Pacer(StateOfPacer* st, int x, int y, int maxx, int maxy, int minx, int miny, int lj)
	{
		state = st;
		coordinates = Coordinates(x, y);
		maxCoordinates = Coordinates(maxx, maxy);
		minCoordinates = Coordinates(minx, miny);

		lengthJamp = lj;
	}
	Pacer(StateOfPacer* st, int x, int y, int x2, int y2, int lj)
	{
		state = st;
		coordinates = Coordinates(x, y);
		maxCoordinates = Coordinates(max(x, x2), max(y, y2));
		minCoordinates = Coordinates(min(x, x2), min(y, y2));

		lengthJamp = lj;
	}
	Pacer(StateOfPacer* st)
	{
		state = st;
		coordinates = Coordinates(0, 0);
		maxCoordinates = Coordinates(10, 10);
		minCoordinates = Coordinates(-10, -10);

		lengthJamp = 1;
	}
	~Pacer()
	{
		delete state;
	}
	void SetState(StateOfPacer* s)
	{
		delete state;
		state = s;
	}

	void printSmth()
	{
		std::cout << "x = " << coordinates.x << " y = " << coordinates.y << " State = " << state->GetName() << std::endl;
	}
	void Step()
	{
		state->Step(this);
	}
	void JampOn(int *arr,int width, int length, int Sconst, int* S)
	{
		for (int i = 0; i <length; ++i)
		{
			if (*S + 1 < Sconst)
			{
				Step();
				++*S;
				arr[coordinates.y * width + coordinates.x] = 1;
			}
		}
	}
	void JampOn(GameObject* arr, int width, int length, int Sconst, int* S)
	{
		for (int i = 0; i < length; ++i)
		{
			if (*S + 1 < Sconst)
			{
				Step();
				++* S;
				arr[coordinates.y * width + coordinates.x].BuildWall();
			}
		}
	}
	void StepBac()
	{
		state->StepBac(this);
	}
	void TurnLeft() 
	{
		state->TurnLeft(this);
	}
	void TurnRight()
	{
		state->TurnRight(this);
	}
	
};

class UpStateOfPacer : public StateOfPacer
{
public:
	UpStateOfPacer() : StateOfPacer("Up") {}
	virtual void Step(Pacer* pacer)
	{
		if (pacer->maxCoordinates.y > pacer->coordinates.y + pacer->lengthJamp)
			pacer->coordinates.y += pacer->lengthJamp;
	}
	virtual void TurnLeft(Pacer* pacer);
	virtual void TurnRight(Pacer* pacer);
	virtual void StepBac(Pacer* pacer)
	{
		if (pacer->minCoordinates.y < pacer->coordinates.y - pacer->lengthJamp)
			pacer->coordinates.y -= pacer->lengthJamp;
	}

};

class DownStateOfPacer : public StateOfPacer
{
public:
	DownStateOfPacer() : StateOfPacer("Down") {}
	virtual void Step(Pacer* pacer)
	{
		if (pacer->minCoordinates.y < pacer->coordinates.y - pacer->lengthJamp)
			pacer->coordinates.y -= pacer->lengthJamp;
	}
	virtual void TurnLeft(Pacer* pacer);
	virtual void TurnRight(Pacer* pacer);
	virtual void StepBac(Pacer* pacer)
	{
		if (pacer->maxCoordinates.y > pacer->coordinates.y + pacer->lengthJamp)
			pacer->coordinates.y += pacer->lengthJamp;
	}

};

class LeftStateOfPacer : public StateOfPacer
{
public:
	LeftStateOfPacer() : StateOfPacer("Left") {}
	virtual void Step(Pacer* pacer)
	{
		if (pacer->minCoordinates.x < pacer->coordinates.x - pacer->lengthJamp)
			pacer->coordinates.x -= pacer->lengthJamp;
	}
	virtual void TurnLeft(Pacer* pacer);
	virtual void TurnRight(Pacer* pacer);
	virtual void StepBac(Pacer* pacer)
	{
		if (pacer->maxCoordinates.x > pacer->coordinates.x + pacer->lengthJamp)
			pacer->coordinates.x += pacer->lengthJamp;
	}

};

class RightStateOfPacer : public StateOfPacer
{
public:
	RightStateOfPacer() : StateOfPacer("Right") {}
	virtual void Step(Pacer* pacer)
	{
		if (pacer->maxCoordinates.x > pacer->coordinates.x + pacer->lengthJamp)
			pacer->coordinates.x += pacer->lengthJamp;
	}
	virtual void StepBac(Pacer* pacer)
	{
		if (pacer->minCoordinates.x < pacer->coordinates.x - pacer->lengthJamp)
			pacer->coordinates.x -= pacer->lengthJamp;
	}
	virtual void TurnLeft(Pacer*);
	virtual void TurnRight(Pacer*);
	

};

void UpStateOfPacer::TurnLeft(Pacer* pacer)
{
	pacer->SetState(new LeftStateOfPacer());
}
void UpStateOfPacer::TurnRight(Pacer* pacer)
{
	pacer->SetState(new RightStateOfPacer());
}

void DownStateOfPacer::TurnLeft(Pacer* pacer)
{
	pacer->SetState(new RightStateOfPacer());
}
void DownStateOfPacer::TurnRight(Pacer* pacer)
{
	pacer->SetState(new LeftStateOfPacer());
}

void LeftStateOfPacer::TurnLeft(Pacer* pacer)
{
	pacer->SetState(new DownStateOfPacer());
}
void LeftStateOfPacer::TurnRight(Pacer* pacer)
{
	pacer->SetState(new UpStateOfPacer());
}

void RightStateOfPacer::TurnLeft(Pacer* pacer)
{
	pacer->SetState(new UpStateOfPacer());
}
void RightStateOfPacer::TurnRight(Pacer* pacer)
{
	pacer->SetState(new DownStateOfPacer());
}



void wall(Pacer* pacer, GameObject* arr, int SegmentHeight,int SegmentWidth, int width)
{
	int Sx = 0;
	int Sy = 0;

	for (int i = 0; i < 4; ++i)
	{
		(*pacer).JampOn(arr, width, (rand()) % (SegmentWidth / 2)+1, SegmentWidth, &Sx);
		(*pacer).TurnLeft();
		(*pacer).JampOn(arr, width, (rand()) % (SegmentHeight / 2)+1, SegmentHeight, &Sy);
		(*pacer).TurnRight();
	}
	(*pacer).JampOn(arr, width, SegmentWidth - Sx, SegmentWidth, &Sx);
	(*pacer).TurnLeft();
	(*pacer).JampOn(arr, width, SegmentHeight  - Sy, SegmentHeight, &Sy);
	(*pacer).JampOn(arr, width, 2, SegmentHeight+2, &Sy);

}


void BuildRandomRoom1(GameObject* arr, int height, int width)   // строим рандомную комнату
{
	Pacer pacer = Pacer(new RightStateOfPacer(), width/2, 0, width, height, -1, -1, 1);
	arr[pacer.coordinates.y * width + pacer.coordinates.x].BuildWall();
	wall(&pacer, arr, height/2-1 , width/2, width);
	wall(&pacer, arr, width / 2-1, height / 2, width);
	wall(&pacer, arr, height / 2-1, width / 2, width);
	wall(&pacer, arr, width / 2-1, height / 2, width);
	
	// скрываем поля находящиеся за пределами стен
	
	for (int i = 0; i < height; ++i)
	{
		int j = 0;
		while (arr[i*width+j].GetState() != "Wall" && j < width)
		{
			arr[i * width + j].Hide();
			++j;
		}
		j = width - 1;
		while (arr[i * width + j].GetState() != "Wall" && 0 < j)
		{
			arr[i * width + j].Hide();
			--j;
		}

	}
}


