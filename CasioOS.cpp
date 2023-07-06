// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "ConsoleRenderer.h"
#include "WindowManager.h"

#include <iostream>
#include <chrono>
#include <thread>

ConsoleRenderer* renderer;
WindowManager* windowManager;

void render_thread()
{
	while (1) {
		windowManager->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


int main()
{
	renderer = new ConsoleRenderer();
	windowManager = new WindowManager(renderer);

	windowManager->update();

	//std::thread renderThread(render_thread);
	//renderThread.join();

    return 0;
}