#include "pch.h"
#include "IApp.h"
#include <chrono>
#include <iostream>

namespace Fig
{
	
	void IApp::Run()
	{
		// Initialize the application (user-defined)
		Init();

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

		m_Running = true;
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

			dt = 1.0 / m_TickRate;
			fpsDT = 1.0 / m_FrameRate;
			// Fixed updates
			while (accumulator >= dt) {
				FixedUpdate(dt);
				accumulator -= dt;
				updateCount++;
			}

			// --- Variable timestep update ---
			// Call Update once per frame (variable delta)
			if (updateElapse >= dt)
			{
				Update(updateElapse);
				updateElapse = 0.0;
			}

			// --- Rendering ---
			// Render at the target frame rate
			if (renderElapse >= fpsDT)
			{
				// (Rendering code should be placed here)
				if (updateCount > 1)
				{
					std::cout << "Updated " << updateCount << " times.\n";
				}
				renderElapse = 0.0;
				updateCount = 0;
			}

			// Optionally, sleep or yield here to reduce CPU usage
			// std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}
