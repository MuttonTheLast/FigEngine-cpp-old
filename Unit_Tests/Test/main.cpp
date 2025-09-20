#include "FigEngine/OS/Window.h" 
#include "FigEngine/Graphics/GraphicsDevice.h" 
#include <iostream>
#include <SDL3/SDL.h>
#include "FigEngine/Application/IApp.h"
using namespace Fig;

class Game : public IApp
{
public:

private:


	// Inherited via IApp
	bool Init() override
	{
		return false;
	}

	void FixedUpdate(double delta) override
	{
	}

	void Update(double delta) override
	{
	}

};


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
	
	Game* game = new Game();
	game->Run();
}