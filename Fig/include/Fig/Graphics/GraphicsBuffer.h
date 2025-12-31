#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsResource.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"
namespace Fig
{
    class GraphicsBuffer : public GraphicsResource
    {
    public:
        GraphicsBuffer(GraphicsDevice* gd, SDL_GPUBufferUsageFlags usage, Uint32 size,
                SDL_PropertiesID props = 0);    
        
        ~GraphicsBuffer();
        
        void Dispose() override;

        SDL_GPUBuffer* GetHandle();
    private:
        SDL_GPUBuffer* m_Handle;
    };
}
