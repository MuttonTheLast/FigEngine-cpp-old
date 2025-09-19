#include "pch.h"
#include "Test.h"
#include "SDL3/SDL.h"
Test::Test()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK))
	{
		throw "Error";
	}
	SDL_Window* window = SDL_CreateWindow("aaa", 800, 600, SDL_WINDOW_RESIZABLE);
	SDL_ShowWindow(window);
}
