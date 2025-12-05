#pragma once

#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"


namespace Fig
{
    class TransferBuffer
    {
    public:
        TransferBuffer(GraphicsDevice* gd,SDL_GPUTransferBufferUsage usage,
                Uint32 size, SDL_PropertiesID props = 0);
        ~TransferBuffer();
        void Dispose();
        
        void* Map(GraphicsDevice* gd, bool cycle = false);
        void Unmap(GraphicsDevice* gd);

        void Upload(SDL_GPUCopyPass* copyPass, Uint32 transferOffset, GraphicsBuffer* buffer,
                Uint32 bufferOffset, Uint32 size, bool cycle = false);

        void Download(SDL_GPUCopyPass* copyPass, GraphicsBuffer* buffer, Uint32 bufferOffset,
                Uint32 size,Uint32 transferOffset, bool cycle = false);

        void Release(GraphicsDevice* gd);

        SDL_GPUTransferBuffer* GetHandle();
    private:
        SDL_GPUTransferBuffer* m_Handle;
        
        enum TransferBufferState
        {
            None = 0,
            Disposed = 1 << 0,
            Mapped = 1 << 1,
            Released = 1 << 2,
        };
        char m_State = TransferBufferState::None;
    };
}
