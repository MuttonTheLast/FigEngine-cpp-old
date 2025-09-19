#pragma once
#include "SDL3/SDL.h"
#include "../OS/Window.h"

namespace Fig
{
	enum GraphicsBackend
	{

		GraphicsBackend_None = SDL_GPU_SHADERFORMAT_PRIVATE,
		GraphicsBackend_Vulkan = SDL_GPU_SHADERFORMAT_SPIRV,
		GraphicsBackend_D3d12 = SDL_GPU_SHADERFORMAT_DXBC | SDL_GPU_SHADERFORMAT_DXIL,
		GraphicsBackend_MSL = SDL_GPU_SHADERFORMAT_MSL,
		GraphicsBackend_Metal = SDL_GPU_SHADERFORMAT_METALLIB,

		GraphicsBackend_D3D12 = GraphicsBackend_D3d12,
		GraphicsBackend_VULKAN = GraphicsBackend_Vulkan,
	};

	class GraphicsDevice
	{
	public:
		static GraphicsDevice* Create(GraphicsBackend backend, bool debug = false);
	public:
		~GraphicsDevice();
		void Dispose();

		bool ClaimWindow(Window* window);
		void ReleaseWindow();
		
	private:
		GraphicsDevice(SDL_GPUShaderFormat shader, bool debug);

		SDL_GPUDevice* m_Device;
		Window* m_Window = NULL;
		bool m_Disposing = false;
	};

	
}

