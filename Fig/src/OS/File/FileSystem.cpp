#include "Fig/OS/File/FileSystem.h"

#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_asyncio.h"
#include "SDL3/SDL_filesystem.h"
#include <string>
namespace Fig
{
    std::string FileSystem::BASE_PATH = "";
    char FileSystem::s_QueueID = 0;
    char FileSystem::s_MaxQueueCount = 0;
    std::vector<SDL_AsyncIOQueue*> FileSystem::s_AsyncQueues(0);

    ankerl::unordered_dense::map<SDL_AsyncIO*, SDL_AsyncIOOutcome> FileSystem::s_Outcomes;

    void FileSystem::Init(std::string_view appName, std::string_view companyName,
            char MaxQueueCount)
    {
        s_MaxQueueCount = MaxQueueCount;
        Logger::Info("Initializing FileSystem...", "App", false);
        
        const char* basePath = SDL_GetBasePath();
        BASE_PATH = std::string(basePath);
        SDL_free((void*)basePath);

        s_AsyncQueues.resize(MaxQueueCount);
        for (int i = 0; i < MaxQueueCount; i++)
        {
            s_AsyncQueues[i] = SDL_CreateAsyncIOQueue();
            if (s_AsyncQueues[i] == nullptr)
            {
                Logger::Critical("Failed to create io queue", "App", false);
                throw "Failed to create io queue";
            }
        }
    }

    void FileSystem::Shutdown()
    {
        for (auto& queue : s_AsyncQueues)
        {
            SDL_DestroyAsyncIOQueue(queue);
        }
        s_AsyncQueues.clear();
    }

    // Update push results to directory
    void FileSystem::Update()
    {
        for (char i = 0; i < s_MaxQueueCount; i++)
        {
            SDL_AsyncIOQueue* queue = s_AsyncQueues[i];
            SDL_AsyncIOOutcome outcome;
            if (SDL_GetAsyncIOResult(queue, &outcome))
            {
                s_Outcomes.insert({ outcome.asyncio, outcome });
            }
        }
    }
    
    // Reafd files that are in application directory asynchronously
    SDL_AsyncIO* FileSystem::ReadGameFile(std::string_view path, void* buffer,
            Uint64 offset, Uint64 length, void* userdata)
    {
        std::string fullPath = BASE_PATH + std::string(path);
        SDL_AsyncIO* asyncIO = SDL_AsyncIOFromFile(fullPath.c_str(), "r");
        if (asyncIO == nullptr)
        {
            Logger::Error("Failed to create async io from file: " + std::string(path), "App", false);
            throw "Failed to create async io from file";
        }

        if (!SDL_ReadAsyncIO(asyncIO, buffer, offset, length, s_AsyncQueues[s_QueueID], userdata)) {
            Logger::Error("Failed to read async io from file: " + std::string(path), "App", false);
            throw "Failed to read async io from file";
        }

        s_QueueID++;
        if (s_QueueID >= s_MaxQueueCount)
        {
            s_QueueID = 0;
        }
        return asyncIO;
    }
}
