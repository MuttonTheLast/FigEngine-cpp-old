#pragma once
#include <SDL3/SDL.h>

namespace Fig
{
    enum ShaderType : char
    {
        ShaderType_Vertex = SDL_GPU_SHADERSTAGE_VERTEX,
        ShaderType_Fragment = SDL_GPU_SHADERSTAGE_FRAGMENT,
        ShaderType_Compute,

        ShaderType_Pixel = ShaderType_Fragment,
    };
}
