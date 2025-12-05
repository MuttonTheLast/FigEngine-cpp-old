#include "Fig/Graphics/Sampler.h"
#include "SDL3/SDL_gpu.h"

namespace Fig 
{
    
    
    inline SDL_GPUSampler* Sampler::CreatePointClamp(GraphicsDevice *gd)
    {
        constexpr SDL_GPUSamplerCreateInfo info
        {
            // nvim did that and im lazy 
            .min_filter = SDL_GPU_FILTER_NEAREST,
                .mag_filter = SDL_GPU_FILTER_NEAREST,
                .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
                .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
        };
        return SDL_CreateGPUSampler(gd->GetHandle(), &info);
    }

    inline SDL_GPUSampler* Sampler::CreatePointWrap(GraphicsDevice *gd)
    {
        constexpr SDL_GPUSamplerCreateInfo info
        {
            .min_filter = SDL_GPU_FILTER_NEAREST,
                .mag_filter = SDL_GPU_FILTER_NEAREST,
                .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
                .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
        };
        return SDL_CreateGPUSampler(gd->GetHandle(), &info);
    }

    inline SDL_GPUSampler* Sampler::CreateLinearClamp(GraphicsDevice *gd)
    {
        constexpr SDL_GPUSamplerCreateInfo info
        {
            .min_filter = SDL_GPU_FILTER_LINEAR,
                .mag_filter = SDL_GPU_FILTER_LINEAR,
                .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
                .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
        };
        return SDL_CreateGPUSampler(gd->GetHandle(), &info);
    }

    inline SDL_GPUSampler* Sampler::CreateLinearWrap(GraphicsDevice *gd)
    {
        constexpr SDL_GPUSamplerCreateInfo info
        {
            .min_filter = SDL_GPU_FILTER_LINEAR,
                .mag_filter = SDL_GPU_FILTER_LINEAR,
                .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
                .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
        };
        return SDL_CreateGPUSampler(gd->GetHandle(), &info);
    }

    inline SDL_GPUSampler* Sampler::CreateAnisotropicClamp(GraphicsDevice *gd)
    {
        constexpr SDL_GPUSamplerCreateInfo info
        {
            .min_filter = SDL_GPU_FILTER_LINEAR,
                .mag_filter = SDL_GPU_FILTER_LINEAR,
                .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
                .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
                .max_anisotropy = 4,
                .enable_anisotropy = true,
        };
        return SDL_CreateGPUSampler(gd->GetHandle(), &info);
    }

    inline SDL_GPUSampler* Sampler::CreateAnisotropicWrap(GraphicsDevice *gd)
    {
        constexpr SDL_GPUSamplerCreateInfo info
        {
            .min_filter = SDL_GPU_FILTER_LINEAR,
                .mag_filter = SDL_GPU_FILTER_LINEAR,
                .mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR,
                .address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
                .max_anisotropy = 4,
                .enable_anisotropy = true,
        };
        return SDL_CreateGPUSampler(gd->GetHandle(), &info);
    }

}
