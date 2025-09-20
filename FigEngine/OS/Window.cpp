#include "pch.h"
#include "Window.h"
namespace Fig
{

	// Static factory method to create a Window with the given properties and flags.
	Window* Window::Create(WindowProps props, SDL_WindowFlags flags)
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
		// Create the window instance
		Window* window = new Window(props.Title, props.Width, props.Height, flags);

		// Center the window if requested
		if (props.Centered)
		{
			window->CenterWindow();
		}

		return window;
	}

	// Constructor: creates the SDL window with the given title, size, and flags.
	Window::Window(std::string title, int width, int height, SDL_WindowFlags flags)
	{
		m_Window = SDL_CreateWindow(title.c_str(), width, height, flags);
	}

	// Destructor: ensures the window is properly disposed.
	Window::~Window()
	{
		Dispose();
	}

	// Releases the SDL window resource if not already disposed.
	void Window::Dispose()
	{
		if (!m_Disposing)
		{
			m_Disposing = true;
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
}