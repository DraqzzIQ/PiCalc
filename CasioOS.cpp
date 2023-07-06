// CasioOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "ConsoleRenderer.h"
#include "WindowManager.h"
#include <iostream>
#include <chrono>
#include <thread>

int fps = 1;
ConsoleRenderer* renderer;
WindowManager* windowManager;

/// <summary>
/// starts a thread that will update and render the window manager at set fps
/// </summary>
void start_render_thread()
{
	int frame_time = 1000 / fps;

	while (1) {
		windowManager->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(frame_time));
	}
}

/// <summary>
/// entry point
/// </summary>
int main()
{
	renderer = new ConsoleRenderer();
	windowManager = new WindowManager(renderer);

	windowManager->update();

	/*std::thread render_thread(start_render_thread);
	render_thread.join();*/

    return 0;
}