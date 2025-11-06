#pragma once

#include "Fig/OS/Window.h"
#include "Fig/Graphics/GraphicsDevice.h"

namespace Fig
{
    // Abstract base class for the main application loop.
    class IApp
    {
    public:
        //static IApp* GetMain();
    private:
        // Main application instance
        static IApp* s_Main;
    public:
        ~IApp();

        // Starts the main application/game loop.
        void Run();

        // Called once at startup for initialization.
        virtual bool Init() = 0;

        // Called at a fixed timestep (e.g., physics updates).
        // @param delta: Time in seconds since last fixed update.
        virtual void FixedUpdate(double delta) = 0;

        // Called once per frame (variable timestep, e.g., game logic, input).
        // @param delta: Time in seconds since last update.
        virtual void Update(double delta) = 0;

		virtual void Draw() = 0;

        int GetTargetTickRate() const;
		int GetTargetFrameRate() const;
		void SetTargetTickRate(int tickRate);
		void SetTargetFrameRate(int frameRate);
    protected:
        IApp(std::string appName, std::string companyName, WindowProps prop, bool debug);

    private:
        std::string m_AppName;
		std::string m_CompanyName;

        // The main application window.
        Window* m_Window;
        
		// The graphics device (e.g., Direct3D, OpenGL, Vulkan).
		GraphicsDevice* m_GraphicsDevice;

		// Target number of updates and fixed updates per second.
        int m_TargetTickRate = 60;

        // Target number of frames rendered per second.
        int m_TargetFrameRate = 60;

        // Controls the main loop; set to false to exit.
        bool m_Running = false;

		bool m_Debug = false;
    };
}

