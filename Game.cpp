#include <iostream>
#include <string>
#include <conio.h>
#include "Room.h"



int main()
{
	Player* player = new Player(Coordinates(0,0),Coordinates(0,0),Coordinates(40,30));
	Room room(player, 40, 30);

	char mod;

	while (true)
	{
		system("cls");
		room.PrintRoom();

		mod = _getch();

		switch (mod)
		{
			case '8':
			{
				room.Up();
				break;
			}
			case '2':
			{
				room.Down();
				break;
			}
			case '4':
			{
				room.Left();
				break;
			}
			case '6':
			{
				room.Right();
				break;
			}
		}
	}

	delete player;


	return 0;
}


