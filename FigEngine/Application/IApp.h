#pragma once

namespace Fig
{
    // Abstract base class for the main application loop.
    class IApp
    {
    public:
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

    private:
		// Target number of updates and fixed updates per second.
        int m_TickRate = 60;

        // Target number of frames rendered per second.
        int m_FrameRate = 60;

        // Controls the main loop; set to false to exit.
        bool m_Running = false;
    };
}

