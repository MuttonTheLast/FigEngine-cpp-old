#pragma once

#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsResource.h"
#include "Fig/Graphics/Texture/Texture.h"
#include "Fig/Utilities/GLMath.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"


namespace Fig
{
    class TransferBuffer : public GraphicsResource
    {
    public:
        static TransferBuffer* CreateTextureBuffer(GraphicsDevice* gd,
                SDL_GPUTransferBufferUsage usage,
                SDL_GPUTextureFormat format, Vector2 size,int depth,
                SDL_PropertiesID props = 0);

        TransferBuffer(GraphicsDevice* gd,SDL_GPUTransferBufferUsage usage,
                Uint32 size, SDL_PropertiesID props = 0);
        ~TransferBuffer();
        void Dispose() override;
        
        void* Map(bool cycle = false);
        void Unmap();

        void Upload(SDL_GPUCopyPass* copyPass, Uint32 transferOffset, GraphicsBuffer* buffer,
                Uint32 bufferOffset, Uint32 size, bool cycle = false);

        void Upload(SDL_GPUCopyPass* copyPass, Uint32 transferOffset, Texture* texture,
                bool cycle = false);

        void Download(SDL_GPUCopyPass* copyPass, GraphicsBuffer* buffer, Uint32 bufferOffset,
                Uint32 size,Uint32 transferOffset, bool cycle = false);

        SDL_GPUTransferBuffer* GetHandle();
    private:
        SDL_GPUTransferBuffer* m_Handle;
        bool m_Mapped = false;
    };
}
