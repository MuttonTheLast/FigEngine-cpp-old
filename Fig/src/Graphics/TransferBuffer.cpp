#include "Fig/Graphics/TransferBuffer.h"
#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"
#include <cstddef>

namespace Fig {
    
    TransferBuffer::TransferBuffer(GraphicsDevice* gd, SDL_GPUTransferBufferUsage usage,
            Uint32 size, SDL_PropertiesID props)
    {
        SDL_GPUTransferBufferCreateInfo createInfo
        (
            usage,
            size,
            props
        );
        m_Handle = SDL_CreateGPUTransferBuffer(gd->GetHandle(), &createInfo);
        if (m_Handle == NULL)
        {
            Logger::Error(SDL_GetError(), "App", false);
        }
    }

    TransferBuffer::~TransferBuffer()
    {
        Dispose();
    }

    void TransferBuffer::Dispose()
    {
        if ((m_State & TransferBufferState::Disposed) == 0)
        {
            m_State |= TransferBufferState::Disposed;
            if ((m_State & TransferBufferState::Released) == 0)
            {
                Logger::Error("Did not released TransferBuffer befor destruction.", "App");
            }
            
        }
    }

    void* TransferBuffer::Map(GraphicsDevice* gd, bool cycle)
    {
        m_State |= TransferBufferState::Mapped;
        return SDL_MapGPUTransferBuffer(gd->GetHandle(), m_Handle, cycle);
    }

    void TransferBuffer::Unmap(GraphicsDevice* gd)
    {
        m_State &= ~TransferBufferState::Mapped;
        return SDL_UnmapGPUTransferBuffer(gd->GetHandle(), m_Handle);
    }

    void TransferBuffer::Upload(SDL_GPUCopyPass* copyPass, Uint32 transferOffset,
            GraphicsBuffer* buffer, Uint32 bufferOffset, Uint32 size, bool cycle)
    {
        SDL_GPUTransferBufferLocation loc(
            m_Handle,
            transferOffset
                );
        SDL_GPUBufferRegion reg(
                buffer->GetHandle(),
                bufferOffset,
                size
                );

        SDL_UploadToGPUBuffer(copyPass, &loc, &reg, cycle);
    }

    void TransferBuffer::Download(SDL_GPUCopyPass* copyPass, GraphicsBuffer* buffer,
            Uint32 bufferOffset, Uint32 size,  Uint32 transferOffset, bool cycle)
    {
        SDL_GPUTransferBufferLocation loc(
            m_Handle,
            transferOffset
                );
        SDL_GPUBufferRegion reg(
                buffer->GetHandle(),
                bufferOffset,
                size
                );
        SDL_DownloadFromGPUBuffer(copyPass, &reg, &loc);
    }

    void TransferBuffer::Release(GraphicsDevice* gd)
    {
        if (m_State & Mapped)
        {
            Logger::Error("Did not unmapped TransferBuffer before release.", "App");
        }
        SDL_ReleaseGPUTransferBuffer(gd->GetHandle(), m_Handle);
        m_State |= TransferBufferState::Released;
    }

    SDL_GPUTransferBuffer* TransferBuffer::GetHandle()
    {
        return m_Handle;
    }

}
