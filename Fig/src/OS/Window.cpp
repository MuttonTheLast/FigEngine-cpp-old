#include "Fig/OS/Window.h"
#include "Fig/Application/IApp.h"
#include "Fig/Utilities/HashMap/ankerl/unordered_dense.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_video.h"
#include <cstddef>
namespace Fig
{
    // ankerl::unordered_dense::map<SDL_Window*, Window*> Window::s_Windows;

	// Constructor: creates the SDL window with the given title, size, and flags.
	Window::Window(const WindowProps& props, SDL_WindowFlags flags)
	{
        
		// Apply window property flags based on WindowProps
		if (props.Fullscreen)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (props.Borderless)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		if (props.Maximized)
		{
			flags |= SDL_WINDOW_MAXIMIZED;
		}
		if (props.Resizable)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if (props.HighDPI)
		{
			flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
		}

		Logger::Info("Creating Window...", "App", true);
		m_Window = SDL_CreateWindow(props.Title.c_str(), props.Width, props.Height, flags);
		if (m_Window == NULL)
		{
			Logger::Error(std::string("Failed to create window: ") + SDL_GetError(), "App", true);
            return;
		}
        // s_Windows.insert({m_Window, this});
        // Center the window if requested
        if (props.Centered)
        {
            CenterWindow();
        }
	}

	// Destructor: ensures the window is properly disposed.
	Window::~Window()
	{
		Dispose();
	}

	// Releases the SDL window resource if not already disposed.
	void Window::Dispose()
	{
		if (!m_Disposed)
		{
			m_Disposed = true;
            // s_Windows.erase(m_Window);
			SDL_DestroyWindow(m_Window);
		}
	}

	// Returns the current size of the window as a Vector2.
	Vector2 Window::GetSize()
	{
		int width, height;
		SDL_GetWindowSize(m_Window, &width, &height);
		return Vector2(width, height);
	}

	// Returns the current position of the window as a Vector2.
	Vector2 Window::GetPos()
	{
		int x, y;
		SDL_GetWindowPosition(m_Window, &x, &y);
		return Vector2(x, y);
	}

	// Sets the window size using width and height. Returns SDL's result.
	bool Window::SetSize(int width, int height)
	{
		return SDL_SetWindowSize(m_Window, width, height);
	}

	// Sets the window size using a Vector2.
	bool Window::SetSize(Vector2 size)
	{
		return SetSize(size.x, size.y);
	}

	// Maximizes the window. Returns SDL's result.
	bool Window::Maximize()
	{
		return SDL_MaximizeWindow(m_Window);
	}

	// Sets the window position using x and y. Returns SDL's result.
	bool Window::SetPos(int x, int y)
	{
		return SDL_SetWindowPosition(m_Window, x, y);
	}

	// Sets the window position using a Vector2.
	bool Window::SetPos(Vector2 pos)
	{
		return SetPos(pos.x, pos.y);
	}

	// Centers the window on the screen.
	bool Window::CenterWindow()
	{
		return SetPos(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}

	// Returns the underlying SDL_Window pointer.
	SDL_Window* Window::GetHandle()
	{
		return m_Window;
	}

	// Implicit conversion operator to SDL_Window*.
	Window::operator SDL_Window* ()
	{
		return GetHandle();
	}

    void Window::SetApp(void* app)
    {
        m_App = app;
    }

    void* Window::GetApp()
    {
        return m_App;
    }

    bool Window::HasApp()
    {
        return m_App != NULL;
    }
}
