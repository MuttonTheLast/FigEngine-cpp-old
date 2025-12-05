#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"
namespace Fig 
{

    class Sampler
    {
    public:
        static SDL_GPUSampler* CreatePointClamp(GraphicsDevice* gd);
        static SDL_GPUSampler* CreatePointWrap(GraphicsDevice* gd);
        static SDL_GPUSampler* CreateLinearClamp(GraphicsDevice* gd);
        static SDL_GPUSampler* CreateLinearWrap(GraphicsDevice* gd);
        static SDL_GPUSampler* CreateAnisotropicClamp(GraphicsDevice* gd);
        static SDL_GPUSampler* CreateAnisotropicWrap(GraphicsDevice* gd);
    };
}
