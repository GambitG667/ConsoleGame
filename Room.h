#pragma once
#include "RandPacer.h"
#include "Screen.h"
#include "Player.h"


//класс комнаты генерирует комнату и выводит ее на экран. хранит только указатель игрока, сам игрок должен лежать на карте
//чтобы реализовать переход между комнат.

class Room
{
private:
	int HEIGHT = 20;
	int WIDTH = 20;
	Player* player;
	GameObject* roomMapArr;

public:

	void PrintRoom()
	{
		ScreenArray sA(roomMapArr, WIDTH, HEIGHT);
		char simbArr[5]{ 32,44,35,64 };
		Screen screen(sA, simbArr);
		screen.print();
	}
	
	//эта порнография - попытка сделать так что бы каждый класс управлял только своими компонентами

	void Up()
	{
		if (roomMapArr[((*player).GetCoord().y - 1) * WIDTH + (*player).GetCoord().x].PlayerTransfer(player))
		{
			roomMapArr[(*player).GetCoord().y * WIDTH + (*player).GetCoord().x].ClearPlayer();
			(*player).StepDown();
		}
	}
	void Down()
	{
		if (roomMapArr[((*player).GetCoord().y + 1) * WIDTH + (*player).GetCoord().x].PlayerTransfer(player))
		{
			roomMapArr[(*player).GetCoord().y * WIDTH + (*player).GetCoord().x].ClearPlayer();
			(*player).StepUp();
		}
	}
	void Left()
	{
		if (roomMapArr[(*player).GetCoord().y * WIDTH + ((*player).GetCoord().x - 1)].PlayerTransfer(player))
		{
			roomMapArr[(*player).GetCoord().y * WIDTH + (*player).GetCoord().x].ClearPlayer();
			(*player).StepLeft();
		}
	}
	void Right()
	{
		if (roomMapArr[(*player).GetCoord().y * WIDTH + ((*player).GetCoord().x + 1)].PlayerTransfer(player))
		{
			roomMapArr[(*player).GetCoord().y * WIDTH + (*player).GetCoord().x].ClearPlayer();
			(*player).StepRight();
		}
	}

	Room(Player* player, int WIDTH, int HEIGHT)
	{
		this->HEIGHT = HEIGHT;
		this->WIDTH = WIDTH;
		this->player = player;
		roomMapArr = new GameObject[HEIGHT * WIDTH];
		BuildRandomRoom1(roomMapArr, HEIGHT, WIDTH);
		(*player).SetCoordinate(WIDTH / 2, HEIGHT / 2);
		roomMapArr[(*player).GetCoord().y * WIDTH + (*player).GetCoord().x].PlayerTransfer(player);
	}
	~Room()
	{
		delete[] roomMapArr;
	}



};
