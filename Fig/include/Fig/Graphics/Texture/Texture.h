#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsResource.h"
#include "Fig/Utilities/GLMath.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include <string_view>
#include <vector>
namespace Fig
{
    class Texture : public GraphicsResource
    {

    public:
        
    public:

        
        // Texture(GraphicsDevice* gd, std::string_view path, int depth = 1, int levels = 1, SDL_GPUTextureUsageFlags usage = SDL_GPU_TEXTUREUSAGE_SAMPLER);
        // Texture(GraphicsDevice* gd, std::vector<Uint8>& data, SDL_GPUTextureFormat format, int width, int height, int depth = 1, int levels = 1, SDL_GPUTextureUsageFlags usage = SDL_GPU_TEXTUREUSAGE_SAMPLER);
        Texture(GraphicsDevice* gd,SDL_GPUTextureType type, SDL_GPUTextureFormat format,
                Uint32 width, Uint32 height, Uint32 depth = 1, Uint32 levels = 1,
                SDL_GPUTextureUsageFlags usage = SDL_GPU_TEXTUREUSAGE_SAMPLER);
        ~Texture();
        void Dispose() override;

        Vector2 GetSize() const;
        void GetSize(Uint32& width, Uint32& height) const;
        Uint32 GetDepth() const;
        Uint32 GetLevels() const;
        Uint32 GetSizeInBytes() const;
        SDL_GPUTexture* GetHandle() const;

    private:
        SDL_GPUTexture* m_Texture = nullptr;
        
        // data
        Uint32 m_Width = 0;
        Uint32 m_Height = 0;
        Uint32 m_Depth = 1;
        Uint32 m_Levels = 1;
        
    };
}
