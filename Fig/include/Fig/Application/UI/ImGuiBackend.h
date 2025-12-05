#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_gpu.h"
#include <FigConfig.h>

#if IS_DESKTOP
#include "Fig/Utilities/ImGui/imgui.h"
#endif // IS_DESKTOP
       
namespace Fig {


    // TODO: Make Imgui more clear
    class ImGuiBackend
    {
    public:
        static void Init(GraphicsDevice* gd, bool multiWindow = false);

        static bool ProcessEvent(SDL_Event* event);

        static void NewFrame();
        static void EndFrame();

        static void PreRender(SDL_GPUCommandBuffer* cmdbuf);

        static void Render(SDL_GPUCommandBuffer* cmdbuf, SDL_GPURenderPass* renderpass);

        static void PostRender();
        
        static void Shutdown();
    private:
#if IS_DESKTOP
        static ImDrawData* s_DrawData;
#endif // IS_DESKTOP
    };
}

