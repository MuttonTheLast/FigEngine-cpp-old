#pragma once
#include <SDL3/SDL.h>
namespace Fig
{

    // Enum representing supported graphics backends for the device
    enum GraphicsBackend
    {
        GraphicsBackend_None = SDL_GPU_SHADERFORMAT_PRIVATE, // No backend
        GraphicsBackend_Vulkan = SDL_GPU_SHADERFORMAT_SPIRV, // Vulkan backend
        GraphicsBackend_D3d12 = SDL_GPU_SHADERFORMAT_DXBC | SDL_GPU_SHADERFORMAT_DXIL, // Direct3D 12 backend
        GraphicsBackend_MSL = SDL_GPU_SHADERFORMAT_MSL,      // Metal Shading Language backend
        GraphicsBackend_Metal = SDL_GPU_SHADERFORMAT_METALLIB, // Metal backend

        // Aliases for consistency
        GraphicsBackend_D3D12 = GraphicsBackend_D3d12,
        GraphicsBackend_VULKAN = GraphicsBackend_Vulkan,
    };
}
