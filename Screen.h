#pragma once
#ifndef	SCREAN_H_
#define SCREEN_H_
#include <iostream>
#include "GameObject.h"

//служебный класс выводит массив GameObject на экран соответственно их обозначениям.

struct ScreenArray
{
	GameObject* screenArray;
	int width;
	int height;
	ScreenArray(GameObject* sA,int w,int h)
	{
		screenArray = sA;
		width = w;
		height = h;
	}
};

class Screen
{
private:

	GameObject* screenArray;

	char *simbolsArray;

	int width;
	int height;

public:

	Screen(ScreenArray screenArr, char(*simbolsArr))
	{
		screenArray = screenArr.screenArray;

		simbolsArray = simbolsArr;

		height = screenArr.height;
		width = screenArr.width;
	}

	void print()
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				std::cout << simbolsArray[screenArray[i * width + j].GetInfo()];
			}
			std::cout << std::endl;
		}
	}
};

#endif
