#pragma once
#include <SDL3/SDL.h>
#include "Fig/Utilities/GLMath.h"
#include <string>

namespace Fig
{
    // Structure to hold window creation properties
    struct WindowProps
    {
        std::string Title;    // Window title
        int Width;            // Window width in pixels
        int Height;           // Window height in pixels
        bool Fullscreen;      // Should the window be fullscreen?
        bool Borderless;      // Should the window have no border?
        bool Centered;        // Should the window be centered on screen?
        bool Maximized;       // Should the window start maximized?
        bool Resizable;       // Should the window be resizable?
        bool HighDPI;         // Should the window support high DPI?

        // Constructor with default values for all properties
        WindowProps(std::string title = "DefualtWindow", int width = 800, int height = 600,
            bool fullscreen = false, bool borderless = false, bool centered = false, bool maximized = false,
            bool resizable = false, bool highDPI = false)
            :Title(title), Width(width), Height(height), Fullscreen(fullscreen), Borderless(borderless),
            Centered(centered), Maximized(maximized), Resizable(resizable), HighDPI(highDPI)
        {
        }
    };

    // Window class encapsulating SDL_Window and related operations
    class Window
    {
    public:
        // Static factory method to create a new Window instance
        static Window* Create(WindowProps props, SDL_WindowFlags flags);

        bool Claimed = false; // Indicates if the window is claimed/owned by a subsystem

    public:
        // Destructor: cleans up resources
        ~Window();

        // Releases the SDL_Window resource if not already disposed
        void Dispose();

        // Returns the current window size as a Vector2 (width, height)
        Vector2 GetSize();

        // Returns the current window position as a Vector2 (x, y)
        Vector2 GetPos();

        // Sets the window size using width and height
        bool SetSize(int width, int height);

        // Sets the window size using a Vector2
        bool SetSize(Vector2 size);

        // Maximizes the window
        bool Maximize();

        // Sets the window position using x and y
        bool SetPos(int x, int y);

        // Sets the window position using a Vector2
        bool SetPos(Vector2 pos);

        // Centers the window on the screen
        bool CenterWindow();

        // Returns the underlying SDL_Window pointer
        SDL_Window* GetHandle();

        // Implicit conversion operator to SDL_Window*
        operator SDL_Window*();

    private:
        // Private constructor: use Create() to instantiate
        Window(std::string title, int width, int height, SDL_WindowFlags flags);

        SDL_Window* m_Window;    // Pointer to the SDL window
        bool m_Disposing = false; // Tracks if the window is being disposed
    };

}
