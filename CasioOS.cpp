// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "ConsoleRenderer.h"
#include <iostream>

ConsoleRenderer *renderer;
bool (*arr)[SCREEN_WIDTH];

void launch_main_menu();

int main()
{
	renderer = new ConsoleRenderer();
	arr = new bool[SCREEN_HEIGHT][SCREEN_WIDTH];

	launch_main_menu();

    return 0;
}

void launch_main_menu()
{

}