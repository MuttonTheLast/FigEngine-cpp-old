#define STB_IMAGE_IMPLEMENTATION

#include "Fig/Utilities/Image/ImgManager.h"
#include "Fig/Utilities/HashMap/ankerl/unordered_dense.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_surface.h"
#include "Fig/Utilities/stb/stb_image.h"

namespace Fig
{

    
    ankerl::unordered_dense::set<SDL_Surface*> ImgManager::s_Surfaces;

    SDL_Surface* ImgManager::SurfaceFromRawData(std::vector<Uint8> &data)
    {
        int w, h, channels;
        void* pixels = stbi_load_from_memory(data.data(), data.size(),
                &w, &h, &channels, 4);

        if (!pixels) {
            SDL_Log("stb_image failed: %s", stbi_failure_reason());
            return NULL;
        }

        // Create SDL surface from raw pixels
        SDL_Surface* surface = SDL_CreateSurfaceFrom(
                w,h,
                SDL_PIXELFORMAT_RGBA32,
                pixels,
                w * 4);
        

        if (!surface) {
            SDL_Log("SDL_CreateSurfaceFrom failed: %s", SDL_GetError());
            stbi_image_free(pixels);
            return NULL;
        }
        s_Surfaces.insert(surface);
        return surface;
    }

    void ImgManager::CleanSurfaceRawData(SDL_Surface *surface)
    {
        if (s_Surfaces.contains(surface)) {
            void* pixels = surface->pixels;
            s_Surfaces.erase(surface);
            SDL_DestroySurface(surface);
            stbi_image_free(surface->pixels);
        }else{
            Logger::Warn("Tried to remove surface that not made from raw data",
                        "App");
        }
    }

}
