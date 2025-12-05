#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <string_view>
#include "Fig/Utilities/HashMap/ankerl/unordered_dense.h"
#include "SDL3/SDL_asyncio.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_storage.h"
#include <vector>

namespace Fig
{
	enum ReadLocation : char
	{
		ReadLocation_App = 0,
		ReadLocation_Save = 1,
		ReadLocation_Docs = 2,

		ReadLocation_Title = ReadLocation_App,
		ReadLocation_User = ReadLocation_Save,
	};

	class FileSystem
	{
    public:
        static void Init(std::string_view appName, std::string_view companyName,
                char MaxQueueCount = 8);
        static void Shutdown();
        static void Update();

        static SDL_AsyncIO* ReadGameFile(std::string_view path, void* buffer,
                Uint64 offset, Uint64 length, void* userdata = nullptr);

    public: // NOTE: SDL_Storage
        static bool ReadFile(const char* path, std::vector<Uint8>& buffer,
                ReadLocation location = ReadLocation_App);
        
    private:
        static std::string BASE_PATH;
        
        static char s_QueueID;
        static char s_MaxQueueCount;
        static std::vector<SDL_AsyncIOQueue*> s_AsyncQueues;
        static ankerl::unordered_dense::map<SDL_AsyncIO*, SDL_AsyncIOOutcome> s_Outcomes;
    
        
    private: // NOTE: SDL_Storage based
        static SDL_Storage* m_Storage;
	};
}

