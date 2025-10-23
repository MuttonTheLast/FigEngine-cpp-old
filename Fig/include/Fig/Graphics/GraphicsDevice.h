#pragma once
#include "SDL3/SDL.h"
#include "../OS/Window.h"

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

    // Class that manages a GPU device and its association with a window
    class GraphicsDevice
    {
    public:
        // Static factory method to create a new GraphicsDevice
        static GraphicsDevice* Create(GraphicsBackend backend, bool debug = false);

    public:
        // Destructor: releases resources
        ~GraphicsDevice();

        // Releases the GPU device and any claimed window
        void Dispose();

        // Claims a window for rendering with this device
        // Returns true on success, false on failure
        bool ClaimWindow(Window* window);

        // Releases the currently claimed window from this device
        void ReleaseWindow();

    private:
        // Private constructor: use Create() to instantiate
        // @param shader: The shader format/backend to use
        // @param debug: Enable debug mode if true
        GraphicsDevice(SDL_GPUShaderFormat shader, bool debug);

        SDL_GPUDevice* m_Device; // Pointer to the underlying SDL GPU device
        Window* m_Window = NULL; // Pointer to the currently claimed window (if any)
        bool m_Disposing = false; // Tracks if the device is being disposed
    };

}

