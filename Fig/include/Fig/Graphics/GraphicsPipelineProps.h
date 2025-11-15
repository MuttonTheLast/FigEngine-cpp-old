#pragma once
#include "SDL3/SDL_gpu.h"
#include <SDL3/SDL.h>
#include <Fig/Graphics/Shader.h>

namespace Fig
{
    struct GraphicsPipelineProps
    {
        Shader* VertexShader;
        Shader* FragmentShader;
        SDL_GPUPrimitiveType PrimitiveType;

        SDL_GPUGraphicsPipelineTargetInfo TargerInfo;
        SDL_GPURasterizerState RasterizerState;
    };
}
