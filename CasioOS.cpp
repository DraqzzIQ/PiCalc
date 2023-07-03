// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "ConsoleRenderer.h"
#include <iostream>

ConsoleRenderer *renderer;
bool (*arr)[96];

int main()
{
	renderer = new ConsoleRenderer();
	arr = new bool[32][96];
	

	renderer->render(arr);

    return 0;
}