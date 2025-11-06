#pragma once
#include <SDL3/SDL.h>
#include <functional>

namespace Fig
{

    enum EventResult : char
    {
        EventResult_None = 0,
        EventResult_Quit = 1,

    };
	class EventHandler
	{
    public:
        // bool function (int, int) :)
        using BoolIntIntFunc = std::function<bool(int,int)>;

	public:
		static EventResult Update();
        static void SetSizeChangeCallback(BoolIntIntFunc callback);
    private:
        static BoolIntIntFunc m_SizeChangeCallback;
	};
}

