#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"

namespace Fig
{

    GraphicsBuffer::GraphicsBuffer(GraphicsDevice* gd, SDL_GPUBufferUsageFlags usage,
            Uint32 size, SDL_PropertiesID props)
    {
        SDL_GPUBufferCreateInfo info(usage, size,props);
        m_Handle = SDL_CreateGPUBuffer(gd->GetHandle(), &info);
    }

    SDL_GPUBuffer* GraphicsBuffer::GetHandle()
    {
        return m_Handle;
    }
}
