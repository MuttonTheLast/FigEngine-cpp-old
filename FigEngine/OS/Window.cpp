#include "pch.h"
#include "Window.h"
namespace Fig
{


	Window* Window::Create(WindowProps props, SDL_WindowFlags flags)
	{
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
		Window* window = new Window(props.Title, props.Width, props.Height, flags);

		if (props.Centered)
		{
			window->CenterWindow();
		}

		return window;
	}
	Window::Window(std::string title, int width, int height, SDL_WindowFlags flags)
	{
		m_Window = SDL_CreateWindow(title.c_str(), width, height, flags);
	}
	Window::~Window()
	{
		Dispose();
	}
	void Window::Dispose()
	{
		if (!m_Disposing)
		{
			m_Disposing = true;
			SDL_DestroyWindow(m_Window);
		}
	}
	Vector2 Window::GetSize()
	{
		int width, height;
		SDL_GetWindowSize(m_Window, &width, &height);
		return Vector2(width, height);
	}
	Vector2 Window::GetPos()
	{
		int x, y;
		SDL_GetWindowPosition(m_Window, &x, &y);
		return Vector2(x, y);
	}
	bool Window::SetSize(int width, int height)
	{
		return SDL_SetWindowSize(m_Window, width, height);
	}
	bool Window::SetSize(Vector2 size)
	{
		return SetSize(size.x, size.y);
	}
	bool Window::Maximize()
	{
		return SDL_MaximizeWindow(m_Window);
	}
	bool Window::SetPos(int x, int y)
	{
		return SDL_SetWindowPosition(m_Window, x, y);
	}
	bool Window::SetPos(Vector2 pos)
	{
		return SetPos(pos.x, pos.y);
	}
	bool Window::CenterWindow()
	{
		return SetPos(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	SDL_Window* Window::GetHandle()
	{
		return m_Window;
	}
	Window::operator SDL_Window* ()
	{
		return GetHandle();
	}
}