#pragma once

#include "Fig/Utilities/HashMap/ankerl/unordered_dense.h"
#include "SDL3/SDL_surface.h"
#include <vector>
namespace Fig
{
    class ImgManager
    {
    public:
        static SDL_Surface* SurfaceFromRawData(std::vector<Uint8>& data);
        static void CleanSurfaceRawData(SDL_Surface* surface);

    private:
        // Create a hash set of surfaces
        static ankerl::unordered_dense::set<SDL_Surface*> s_Surfaces;
    };
}
