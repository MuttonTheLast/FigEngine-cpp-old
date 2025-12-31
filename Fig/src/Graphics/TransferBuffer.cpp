#include "Fig/Graphics/TransferBuffer.h"
#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/Texture/Texture.h"
#include "Fig/Utilities/GLMath.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_properties.h"
#include "SDL3/SDL_stdinc.h"
#include <cstddef>

namespace Fig {
    
    TransferBuffer::TransferBuffer(GraphicsDevice* gd, SDL_GPUTransferBufferUsage usage,
            Uint32 size, SDL_PropertiesID props)
        :GraphicsResource(gd)
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

    TransferBuffer* TransferBuffer::CreateTextureBuffer(GraphicsDevice *gd,
            SDL_GPUTransferBufferUsage usage,
            SDL_GPUTextureFormat format, Vector2 size, int depth,
            SDL_PropertiesID props)
    {
        int pixelSize = 1;
        switch (format)
        {
            //
            //
            case SDL_GPU_TEXTUREFORMAT_R8_UNORM:
            case SDL_GPU_TEXTUREFORMAT_R8_SNORM:
            case SDL_GPU_TEXTUREFORMAT_R8_UINT:
                pixelSize = 1;
                break;

            case SDL_GPU_TEXTUREFORMAT_R8G8_UNORM:
            case SDL_GPU_TEXTUREFORMAT_R8G8_SNORM:
            case SDL_GPU_TEXTUREFORMAT_R8G8_UINT:
                pixelSize = 2;
                break;

            case SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM:
            case SDL_GPU_TEXTUREFORMAT_R8G8B8A8_SNORM:
            case SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UINT:
                pixelSize = 4;
                break;

                //
                // 16bit formats (2 bytes per channel)
                //
            case SDL_GPU_TEXTUREFORMAT_R16_UNORM:
            case SDL_GPU_TEXTUREFORMAT_R16_SNORM:
            case SDL_GPU_TEXTUREFORMAT_R16_UINT:
            case SDL_GPU_TEXTUREFORMAT_R16_FLOAT:
                pixelSize = sizeof(Uint16);
                break;

            case SDL_GPU_TEXTUREFORMAT_R16G16_UNORM:
            case SDL_GPU_TEXTUREFORMAT_R16G16_SNORM:
            case SDL_GPU_TEXTUREFORMAT_R16G16_UINT:
            case SDL_GPU_TEXTUREFORMAT_R16G16_FLOAT:
                pixelSize = sizeof(Uint16) * 2;
                break;

            case SDL_GPU_TEXTUREFORMAT_R16G16B16A16_UNORM:
            case SDL_GPU_TEXTUREFORMAT_R16G16B16A16_SNORM:
            case SDL_GPU_TEXTUREFORMAT_R16G16B16A16_UINT:
            case SDL_GPU_TEXTUREFORMAT_R16G16B16A16_FLOAT:
                pixelSize = sizeof(Uint16) * 4;
                break;

                //
                // 32bit formats (4 bytes per channel)
                //
            case SDL_GPU_TEXTUREFORMAT_R32_UINT:
            case SDL_GPU_TEXTUREFORMAT_R32_FLOAT:
                pixelSize = sizeof(Uint32);
                break;

            case SDL_GPU_TEXTUREFORMAT_R32G32_UINT:
            case SDL_GPU_TEXTUREFORMAT_R32G32_FLOAT:
                pixelSize = sizeof(Uint32) * 2;
                break;

            case SDL_GPU_TEXTUREFORMAT_R32G32B32A32_UINT:
            case SDL_GPU_TEXTUREFORMAT_R32G32B32A32_FLOAT:
                pixelSize = sizeof(Uint32) * 4;
                break;

                //
                // Depth formats
                //
            case SDL_GPU_TEXTUREFORMAT_D16_UNORM:
                pixelSize = 2;
                break;

            case SDL_GPU_TEXTUREFORMAT_D24_UNORM:
                pixelSize = 3;
                break;

            case SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT:
                pixelSize = 4; // 24-bit depth + 8-bit stencil
                break;

            case SDL_GPU_TEXTUREFORMAT_D32_FLOAT:
                pixelSize = 4;
                break;

            case SDL_GPU_TEXTUREFORMAT_D32_FLOAT_S8_UINT:
                pixelSize = 5; // 32-bit depth + 8-bit stencil
                break;

                //
                // Compressed formats (block‑compressed)
                // These do NOT have per‑pixel sizes — they use block sizes.
                //
            case SDL_GPU_TEXTUREFORMAT_BC1_RGBA_UNORM:
                pixelSize = 8; // per 4×4 block
                break;

            case SDL_GPU_TEXTUREFORMAT_BC2_RGBA_UNORM:
            case SDL_GPU_TEXTUREFORMAT_BC3_RGBA_UNORM:
                pixelSize = 16; // per 4×4 block
                break;

            default:
                Logger::Error("Unsupported texture format for transfer buffer.", "App");
                break;
        }
        return new TransferBuffer(gd, usage, size.x * size.y * depth * pixelSize, props);
    }

    TransferBuffer::~TransferBuffer()
    {
        Dispose();
    }

    void TransferBuffer::Dispose()
    {
        if (m_Disposed)
            return;
        if (m_Mapped) 
        {
            Logger::Warn("Tried to dispose a mapped TransferBuffer.", "App");
            return;
        }
        if (m_Handle != NULL)
        {
            SDL_ReleaseGPUTransferBuffer(m_GraphicsDevice->GetHandle(), m_Handle);
            m_Handle = NULL;
        }

        m_Disposed = true;
    }

    void* TransferBuffer::Map(bool cycle)
    {
        if (m_Mapped)
        {
            Logger::Warn("Tried to map an already mapped TransferBuffer.", "App");
            return nullptr;
        }
        m_Mapped = true;
        return SDL_MapGPUTransferBuffer(m_GraphicsDevice->GetHandle(), m_Handle, cycle);
    }

    void TransferBuffer::Unmap()
    {
        if (!m_Mapped)
        {
            Logger::Warn("Tried to unmap an unmapped TransferBuffer.", "App");
            return;
        }
        SDL_UnmapGPUTransferBuffer(m_GraphicsDevice->GetHandle(), m_Handle);
        m_Mapped = false;
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

    void TransferBuffer::Upload(SDL_GPUCopyPass* copyPass, Uint32 transferOffset, Texture* texture,
            bool cycle)
    {
        SDL_GPUTextureTransferInfo loc(
                m_Handle,
                transferOffset
                );
        // LAZY-FIXME: select layer and mipmap and depth
        //      maybe i should do it automatically?
        //      works for now
        SDL_GPUTextureRegion reg{
            .texture = texture->GetHandle(),
            .d = 1
        };
        texture->GetSize(reg.w, reg.h);
        
        SDL_UploadToGPUTexture(copyPass, &loc, &reg, cycle);
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

    SDL_GPUTransferBuffer* TransferBuffer::GetHandle()
    {
        return m_Handle;
    }

}
