#include "Fig/Application/UI/ImGuiBackend.h"
#include "Fig/Graphics/Desktop/ShaderCross.h"
#include "Fig/Graphics/GraphicsBackend.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_hints.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_stdinc.h"
#include "pch.h"
#include "Fig/Application/IApp.h"
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <type_traits>
#include "Fig/OS/EventHandler.h"
#include "Fig/OS/Input/Input.h"
#include "Fig/Utilities/Log/Logger.h"
#include  "Fig/OS/File/FileSystem.h"
#include "quill/core/MacroMetadata.h"
#include <FigConfig.h>
#include "FigConfig.h"

#if IS_DESKTOP
    #include <SDL3_shadercross/SDL_shadercross.h>
#endif

namespace Fig
{
	/*IApp* IApp::GetMain()
	{
		return s_Main;
	}*/
	void IApp::Run()
	{
        if (m_Running)
        {
            Logger::Warn("Tried to run application when running", "App");
            return;
        }
        m_Running = true;

		Logger::Info("App init stage.", "App", true);
		// Initialize the application (user-defined)
		if (!Init())
        {
            Logger::Error("Failed to initialize user data", "App");
            m_Running = false;
            return;
        }
        ImGuiBackend::Init(m_GraphicsDevice, true);
		// Get the current high-resolution time point
		auto now = std::chrono::high_resolution_clock::now();
		// Store the previous time in microseconds
		double previousTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
		double currentTime = 0.0;
		double elapsed = 0.0;

		// Accumulators for fixed update, rendering, and variable update
		double accumulator = 0.0;
		double renderElapse = 0.0;
		double updateElapse = 0.0;

		// Time step for fixed update and rendering
		double dt = 0.0;      // Fixed update timestep (e.g., 1/144s)
		double fpsDT = 0.0;  // Render timestep (e.g., 1/60s)

		unsigned int updateCount = 0;

		Logger::Info("Starting main loop.", "App", true);
		while (m_Running)
		{
			// Calculate elapsed time since last frame
			now = std::chrono::high_resolution_clock::now();
			currentTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
			elapsed = (currentTime - previousTime) / 1000000.0; // Convert microseconds to seconds
			previousTime = currentTime;

			// Accumulate elapsed time for fixed update and rendering
			accumulator += elapsed;
			renderElapse += elapsed;
			updateElapse += elapsed;

			dt = 1.0 / m_TargetTickRate;
			fpsDT = 1.0 / m_TargetFrameRate;


			// --- Variable timestep update ---
			// Call Update once per tick
			if (updateElapse >= dt)
			{
				Input::Update(updateElapse);
                // TODO: Better event result management
				if (EventHandler::Update() == EventResult_Quit) {
				    m_Running = false;
				}
                
				Update(updateElapse);
                ImGuiBackend::NewFrame();
                ImGuiUpdate(updateElapse);
                ImGuiBackend::EndFrame();
				updateElapse = 0;
			}

			// Fixed updates
			while (accumulator >= dt) {
                FileSystem::Update();
				FixedUpdate(dt);
				accumulator -= dt;
				updateCount++;
			}

			// --- Rendering ---
			// Render at the target frame rate
			if (m_TargetFrameRate == 0 || renderElapse >= fpsDT)
			{
				// (Rendering code should be placed here)
				if (updateCount > 1)
				{
					Logger::Info("FixUpdated " + std::to_string(updateCount) + " times before render.", "App", false);
				}
				Render();
				renderElapse = 0.0;
				updateCount = 0;
			}

			// Optionally, sleep or yield here to reduce CPU usage
			// std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
        ImGuiBackend::Shutdown();
	}
	int IApp::GetTargetTickRate() const
	{
		return m_TargetTickRate;
	}
	int IApp::GetTargetFrameRate() const
	{
		return m_TargetFrameRate;
	}
	void IApp::SetTargetTickRate(int tickRate)
	{ 
		m_TargetTickRate = tickRate;
	}
	void IApp::SetTargetFrameRate(int frameRate)
	{
		m_TargetFrameRate = frameRate;
	}

    GraphicsBackend IApp::GetBackend()
    {
        return m_Backend;
    }

    void IApp::Render()
    {
        SDL_GPUCommandBuffer* cmdbuf = m_GraphicsDevice->AcquireCommandBuffer();

        if (cmdbuf == NULL)
        {
            Logger::Error("Could not acquire command buffer.", "App");
            return;
        }
        ImGuiBackend::PreRender(cmdbuf);
        PreRender(cmdbuf);
        if (!SDL_AcquireGPUSwapchainTexture(cmdbuf, m_Window->GetHandle(),&m_SwapchainTexture, NULL, NULL)) {
            SDL_Log("AcquireGPUSwapchainTexture failed: %s", SDL_GetError());
            return;
        }
        if (m_SwapchainTexture != NULL)
        {
            SDL_GPUColorTargetInfo colorTargetInfo = { 0 };
            colorTargetInfo.texture = m_SwapchainTexture;
            colorTargetInfo.clear_color = m_GraphicsDevice->GetClearColor();
            colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
            colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

            SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdbuf, &colorTargetInfo, 1, NULL);

            Render(cmdbuf, renderPass);
            ImGuiBackend::Render(cmdbuf, renderPass);
            SDL_EndGPURenderPass(renderPass);
        }
        
        ImGuiBackend::PostRender();

        SDL_SubmitGPUCommandBuffer(cmdbuf);
    }
	IApp::IApp(std::string appName, std::string companyName, WindowProps props, bool debug)
		:m_AppName(appName), m_CompanyName(companyName), m_Debug(debug), m_Window(NULL)
	{
        // TODO: Better file debug management
		Logger::Init(debug, true);
		Logger::Info("Starting Application: " + m_AppName, "App", true);
		Logger::Info("Initializing SDL...", "App", true);

#if LINUX
        // Force X11 driver via environment variable if needed
        setenv("SDL_VIDEODRIVER", "x11", 1);
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "x11");

#endif
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
		{
			Logger::Critical(std::string("SDL initialize failed: \n") + SDL_GetError(), "App", true);
			throw SDL_GetError();
            return;
		}
        
        const char *driver = SDL_GetCurrentVideoDriver();
        if (driver) {
            Logger::Info("SDL is using video driver: " + std::string(driver), "App");
        } else {
            Logger::Critical("No Video driver active!", "App");
        }
#if IS_DESKTOP
        Logger::Info("Initializing ShaderCross", "App");
        if (!ShaderCross::Init())
        {
            Logger::Critical("ShaderCross initialize failed", "App");
            throw SDL_GetError();
            return;
        }
#endif // IS_DESKTOP
        FileSystem::Init(appName, companyName);

        // TODO: Make backend selectable or at least find backend by launch options or automatic
#if LINUX
        m_Backend = GraphicsBackend_Vulkan;
#elif WINDOWS
        m_Backend = GraphicsBackend_D3D12;
#endif

		m_Window = new Window(props, 0);
        m_GraphicsDevice = new GraphicsDevice(m_Backend, debug);
		m_GraphicsDevice->ClaimWindow(m_Window);
		Logger::Info("Application fully initialized.", "App", true);
	}
	IApp::~IApp()
	{
        delete m_GraphicsDevice;
        delete m_Window;
#if IS_DESKTOP
        SDL_ShaderCross_Quit();
#endif
        SDL_Quit();
        // TODO: Shutdown for Logger (OS does that so its not important yet.)
	}
}
