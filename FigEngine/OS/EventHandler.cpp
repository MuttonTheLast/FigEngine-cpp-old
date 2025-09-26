#include "pch.h"
#include "EventHandler.h"
#include "Input/Input.h"
namespace Fig
{
	void EventHandler::Update()
	{

		SDL_Event event;
		while (SDL_PollEvent(&event)) {  
			if (Input::HandleEvent(event))
			{
				return;
			}
		}
	}
}