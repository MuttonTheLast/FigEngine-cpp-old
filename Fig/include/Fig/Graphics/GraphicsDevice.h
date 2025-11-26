#pragma once
#include "../OS/Window.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_pixels.h"
#include "GraphicsBackend.h"
namespace Fig
{

    // Class that manages a GPU device and its association with a window
    class GraphicsDevice
    {
    /* idk why i have made create when im not using C# :|
     * public:
        // Static factory method to create a new GraphicsDevice
        static GraphicsDevice* Create(GraphicsBackend backend, bool debug = false);
    */
    public:
        // Private constructor: use Create() to instantiate
        // @param shader: The shader format/backend to use
        // @param debug: Enable debug mode if true
        GraphicsDevice(GraphicsBackend shader, bool debug);

        // Destructor: releases resources
        ~GraphicsDevice();

        // Releases the GPU device and any claimed window
        void Dispose();

        // Claims a window for rendering with this device
        // Returns true on success, false on failure
        bool ClaimWindow(Window* window);

        // Releases the currently claimed window from this device
        void ReleaseWindow();
        
        SDL_GPUCommandBuffer* AcquireCommandBuffer();
        
        void SetClearColor(const SDL_FColor& color);
        const SDL_FColor& GetClearColor();

        SDL_GPUDevice* GetHandle() const;
    private:
        
        SDL_FColor m_ClearColor = (SDL_FColor){0,0,0,1};
        SDL_GPUDevice* m_Device; // Pointer to the underlying SDL GPU device
        Window* m_Window = NULL; // Pointer to the currently claimed window (if any)
        bool m_Disposing = false; // Tracks if the device is being disposed
    };

}

