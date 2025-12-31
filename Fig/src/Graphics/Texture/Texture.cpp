#include "Fig/Graphics/Texture/Texture.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include <cstddef>

namespace Fig
{
    Texture::Texture(GraphicsDevice* gd,SDL_GPUTextureType type, SDL_GPUTextureFormat format,
            Uint32 width, Uint32 height, Uint32 depth, Uint32 levels, SDL_GPUTextureUsageFlags usage)
        :GraphicsResource(gd), m_Width(width), m_Height(height), m_Depth(depth), m_Levels(levels)
    {

        SDL_GPUTextureCreateInfo info = 
        {
            .type = type,
            .format = format,
            .usage = usage,
            .width = width,
            .height = height,
            .layer_count_or_depth = depth,
            .num_levels = levels,
        };
        m_Texture = SDL_CreateGPUTexture(gd->GetHandle(), &info);
        if (!m_Texture) {
            Logger::Error("Failed to create texture", "App");
            return;
        }
        
    }

    Texture::~Texture()
    {
        Dispose();
    }

    void Texture::Dispose()
    {
        if (m_Disposed)
            return;

        if (m_Texture) {
            SDL_ReleaseGPUTexture(m_GraphicsDevice->GetHandle(), m_Texture);
            m_Texture = NULL;
        }
        m_Texture = NULL;
        m_GraphicsDevice = NULL;
        m_Disposed = true;
    }

    Vector2 Texture::GetSize() const
    {
        return Vector2((float)m_Width, (float)m_Height);
    }

    void Texture::GetSize(Uint32& width, Uint32& height) const
    {
        width = m_Width;
        height = m_Height;
    }

    Uint32 Texture::GetDepth() const
    {
        return m_Depth;
    }

    Uint32 Texture::GetLevels() const
    {
        return GetDepth();
    }

    Uint32 Texture::GetSizeInBytes() const
    {
        // TODO: Calculate based on format
        return m_Width * m_Height * m_Depth * 4;
    }

    SDL_GPUTexture* Texture::GetHandle() const
    {
        return m_Texture;
    }

}
