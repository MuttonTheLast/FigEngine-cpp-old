#include "FigEngine/OS/Window.h" 
#include "FigEngine/Graphics/GraphicsDevice.h" 
#include <iostream>
#include <SDL3/SDL.h>
using namespace Fig;
int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK))
	{
		// TODO: Log Error
		throw SDL_GetError();
	}

	WindowProps props("test");
	
	Window* window = Window::Create(props, NULL);
	GraphicsDevice* device = GraphicsDevice::Create(GraphicsBackend_D3D12, true);
	device->ClaimWindow(window);
	// ! day one finished 
	while (true)
	{

	}
}