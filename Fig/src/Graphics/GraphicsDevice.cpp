#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_pixels.h"
#include "pch.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Utilities/Log/Logger.h"
namespace Fig
{
	// Static factory method to create a new GraphicsDevice instance
	GraphicsDevice* GraphicsDevice::Create(GraphicsBackend backend, bool debug)
	{
		GraphicsDevice* device = new GraphicsDevice(backend, debug);
		return device;
	}

	// Destructor: ensures resources are released
	GraphicsDevice::~GraphicsDevice()
	{
		Dispose();
	}

	// Releases the GPU device and any claimed window
	void GraphicsDevice::Dispose()
	{
		if (!m_Disposing)
		{
			m_Disposing = true;
			ReleaseWindow(); // Unclaim and release the window if any
			SDL_DestroyGPUDevice(m_Device); // Destroy the GPU device
		}
	}

	// Claims a window for this graphics device
	// Returns true on success, throws and returns false on failure
	bool GraphicsDevice::ClaimWindow(Window* window)
	{
		if (m_Window != NULL)
		{
			// Window already claimed by this device
			Logger::Warn("Graphics device already have window.", "App", true);
			return false;
		}
		if (window->Claimed)
		{
			// Window already claimed by another device
			Logger::Warn("Window already claimed by another device.", "App", true);
			return false;
		}
		if (!SDL_ClaimWindowForGPUDevice(m_Device, window->GetHandle()))
		{
			// SDL failed to claim the window for the GPU device
			Logger::Error(std::string("Failed to claim window for graphics device: ") + SDL_GetError(), "App", true);
			return false;
		}
		window->Claimed = true;
		m_Window = window;
		return true;
	}

	// Releases the currently claimed window from this graphics device
	void GraphicsDevice::ReleaseWindow()
	{
		if (m_Window == NULL)
		{
			return;
		}
		SDL_ReleaseWindowFromGPUDevice(m_Device, m_Window->GetHandle());
		m_Window->Claimed = false;
		m_Window = NULL;
	}

    SDL_GPUCommandBuffer* GraphicsDevice::AcquireCommandBuffer()
    {
        return SDL_AcquireGPUCommandBuffer(m_Device);
    }

    void GraphicsDevice::SetClearColor(const SDL_FColor& color)
    {
        m_ClearColor = color;
    }

    const SDL_FColor& GraphicsDevice::GetClearColor()
    {
        return m_ClearColor;
    }

	// Constructor: creates the GPU device with the specified shader format and debug flag
	GraphicsDevice::GraphicsDevice(SDL_GPUShaderFormat shader, bool debug)
	{
		Logger::Info("Creating GraphicsDevice...", "App", true);
		m_Device = SDL_CreateGPUDevice(shader, debug, NULL);
		if (!m_Device)
		{
			Logger::Error(std::string("Failed to create graphics device: ") + SDL_GetError(), "App", true);
		}
	}

}
