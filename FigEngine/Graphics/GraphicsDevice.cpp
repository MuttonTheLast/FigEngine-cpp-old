#include "pch.h"
#include "GraphicsDevice.h"

namespace Fig
{
	GraphicsDevice* GraphicsDevice::Create(GraphicsBackend backend, bool debug)
	{

		GraphicsDevice* device = new GraphicsDevice(backend, debug);
		return device;
	}

	GraphicsDevice::~GraphicsDevice()
	{
		Dispose();
	}

	void GraphicsDevice::Dispose()
	{
		if (!m_Disposing)
		{
			m_Disposing = true;
			ReleaseWindow();
			SDL_DestroyGPUDevice(m_Device);
		}
	}

	bool GraphicsDevice::ClaimWindow(Window* window)
	{
		if (m_Window != NULL)
		{
			// TODO: Log Error
			throw "Graphics device already have window.";
			return false;
		}
		if (window->Claimed)
		{
			// TODO: Log Error
			throw "Window already claimed.";
			return false;
		}
		if (!SDL_ClaimWindowForGPUDevice(m_Device, window->GetHandle()))
		{
			// TODO: Log Error
			throw SDL_GetError();
			return false;
		}
		window->Claimed = true;
		m_Window = window;
		return true;
	}

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

	GraphicsDevice::GraphicsDevice(SDL_GPUShaderFormat shader, bool debug)
	{
		m_Device = SDL_CreateGPUDevice(shader, debug, NULL);
	}

}