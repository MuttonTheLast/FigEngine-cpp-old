#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"

namespace Fig
{

    GraphicsBuffer::GraphicsBuffer(GraphicsDevice* gd, SDL_GPUBufferUsageFlags usage,
            Uint32 size, SDL_PropertiesID props)
        :GraphicsResource(gd)
    {
        SDL_GPUBufferCreateInfo info(usage, size,props);
        m_Handle = SDL_CreateGPUBuffer(gd->GetHandle(), &info);
    }

    // TODO: Destruct i guess :|
    GraphicsBuffer::~GraphicsBuffer()
    {
        Dispose();
    }

    void GraphicsBuffer::Dispose()
    {
        if (m_Disposed)
            return;

        if (m_Handle != NULL)
        {
            SDL_ReleaseGPUBuffer(m_GraphicsDevice->GetHandle(), m_Handle);
            m_Handle = NULL;
        }

        m_Disposed = false;
    }

    SDL_GPUBuffer* GraphicsBuffer::GetHandle()
    {
        return m_Handle;
    }

}
