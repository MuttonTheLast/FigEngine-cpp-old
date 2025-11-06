#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_events.h"
#include "pch.h"
#include "Fig/OS/EventHandler.h"
#include "Fig/OS/Input/Input.h"
namespace Fig
{
    
    EventHandler::BoolIntIntFunc EventHandler::m_SizeChangeCallback = nullptr;

	EventResult EventHandler::Update()
	{

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
            {
                return EventResult_Quit;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                if (!m_SizeChangeCallback)
                {
                    continue;
                }
                if (!m_SizeChangeCallback(event.window.data1, event.window.data2))
                {
                    Logger::Error("Window resize callback returns false", "App");
                }
                continue;
            }
            else if (Input::HandleEvent(event))
			{

				continue;
			}
		}
        return EventResult_None;
	}

    void EventHandler::SetSizeChangeCallback(BoolIntIntFunc callback)
    {
        m_SizeChangeCallback = callback;
    }
}
