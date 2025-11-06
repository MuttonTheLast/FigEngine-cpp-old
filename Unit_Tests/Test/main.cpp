#include "Fig/OS/Window.h" 
#include <SDL3/SDL.h>
#include "Fig/Application/IApp.h"
#include <unistd.h>
#include <Fig/OS/EventHandler.h>
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
        EventHandler::SetSizeChangeCallback( [this](int width, int height) 
                { return SizeChangeCallback(width, height); });

		return true;
	}

    bool SizeChangeCallback(int width, int height)
    {
        
        return true;
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
	void Render(SDL_GPUCommandBuffer* cmdbuff, SDL_GPURenderPass* renderpass) override
	{
        
        

	}

public:

};


int main()
{
	WindowProps props("test");
    props.Resizable = true;

	Game* game = new Game("DefaultGame", "Fig", props, true);
	game->Run();
    return 0;
}
