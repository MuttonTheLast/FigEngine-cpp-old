#include "FigEngine/OS/Window.h" 
#include "FigEngine/Graphics/GraphicsDevice.h" 
#include <iostream>
#include <SDL3/SDL.h>
#include "FigEngine/Application/IApp.h"
#include "FigEngine/OS/Input/Input.h"
#include "FigEngine/Utilities/Log/Logger.h"
using namespace Fig;

class Game : public IApp
{
public:
	Game(std::string appName, std::string companyName, WindowProps prop, bool debug)
		:IApp(appName, companyName, prop, debug)
	{

	}
private:


	// Inherited via IApp
	bool Init() override
	{
		return false;
	}

	void FixedUpdate(double delta) override
	{
	}
	double updateCount = 0;
	void Update(double delta) override
	{
		updateCount += delta;

	}


	// Inherited via IApp
	void Draw() override
	{
	}

public:

};


int main()
{

	WindowProps props("test");
	
	
	Game* game = new Game("DefaultGame", "Fig", props, true);
	game->Run();
}