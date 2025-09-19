#pragma once
#include <SDL3/SDL.h>
#include "../Utilities/GLMath.h"
#include <string>
namespace Fig
{
	struct WindowProps
	{
		std::string Title;
		int Width;
		int Height;
		bool Fullscreen;
		bool Borderless;
		bool Centered;
		bool Maximized;
		bool Resizable;
		bool HighDPI;

		WindowProps(std::string title = "DefualtWindow", int width = 800, int height = 600,
			bool fullscreen = false, bool borderless = false, bool centered = false, bool maximized = false,
			bool resizable = false, bool highDPI = false)
			:Title(title), Width(width), Height(height), Fullscreen(fullscreen), Borderless(borderless),
			Centered(centered), Maximized(maximized), Resizable(resizable), HighDPI(highDPI)
		{
		}
	};


	class Window
	{
	public:
		static Window* Create(WindowProps props, SDL_WindowFlags flags);

		bool Claimed = false;
	public:
		~Window();
		void Dispose();
		Vector2 GetSize();
		Vector2 GetPos();
		bool SetSize(int width, int height);
		bool SetSize(Vector2 size);
		bool Maximize();
		bool SetPos(int x, int y);
		bool SetPos(Vector2 pos);
		bool CenterWindow();
		SDL_Window* GetHandle();

		operator SDL_Window*();
	private:
		Window(std::string title, int width, int height, SDL_WindowFlags flags);

		SDL_Window* m_Window;
		
		bool m_Disposing = false;
	};

}