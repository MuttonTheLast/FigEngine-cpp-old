#include "Fig/Application/UI/ImGuiBackend.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"

#if IS_DESKTOP
#include "Fig/Utilities/ImGui/imgui.h"
#include "../../Utilities/ImGui/backends/imgui_impl_sdl3.h"
#include "../../Utilities/ImGui/backends/imgui_impl_sdlgpu3.h"
#endif

namespace Fig {

#if IS_DESKTOP
    ImDrawData* ImGuiBackend::s_DrawData = nullptr;
#endif // IS_DESKTOP

    void ImGuiBackend::Init(GraphicsDevice* gd, bool multiwindow)
    {
#if IS_DESKTOP
        float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        if (multiwindow)
        {
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        }

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup scaling
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
        io.ConfigDpiScaleFonts = true;          // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
        io.ConfigDpiScaleViewports = true;      // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        if (multiwindow)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        
        // Setup Platform/Renderer backends
        ImGui_ImplSDL3_InitForSDLGPU(gd->GetWindow()->GetHandle());
        ImGui_ImplSDLGPU3_InitInfo init_info = {};
        init_info.Device = gd->GetHandle();
        init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(
                gd->GetHandle(),
                gd->GetWindow()->GetHandle()
                );
        init_info.MSAASamples = SDL_GPU_SAMPLECOUNT_1;                      // Only used in multi-viewports mode.
        init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;  // Only used in multi-viewports mode.
        init_info.PresentMode = SDL_GPU_PRESENTMODE_IMMEDIATE;
        ImGui_ImplSDLGPU3_Init(&init_info);
#endif
    }

    bool ImGuiBackend::ProcessEvent(SDL_Event* event)
    {
#if IS_DESKTOP
        // TODO: if handle ui then dont input to game;
        // Maybe i should write ProcessEvent myself or edit the defult sdl one
        ImGui_ImplSDL3_ProcessEvent(event);
        
#endif
        return false;
    }

    void ImGuiBackend::NewFrame()
    {
#if IS_DESKTOP
        
        // Start the Dear ImGui frame
        ImGui_ImplSDLGPU3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
#endif
    }

    void ImGuiBackend::EndFrame()
    {
#if IS_DESKTOP
        // Rendering
        ImGui::Render();
        s_DrawData = ImGui::GetDrawData();
        const bool is_minimized = (s_DrawData->DisplaySize.x <= 0.0f || s_DrawData->DisplaySize.y <= 0.0f);
#endif
    }

    
    void ImGuiBackend::PreRender(SDL_GPUCommandBuffer* cmdbuf)
    {
#if IS_DESKTOP
        ImGui_ImplSDLGPU3_PrepareDrawData(s_DrawData, cmdbuf);

#endif // IS_DESKTOP
    }

    void ImGuiBackend::Render(SDL_GPUCommandBuffer* cmdbuf, SDL_GPURenderPass* renderpass)
    {
#if IS_DESKTOP
        // Render ImGui
        ImGui_ImplSDLGPU3_RenderDrawData(s_DrawData, cmdbuf, renderpass);
#endif // IS_DESKTOP
    }

    void ImGuiBackend::PostRender()
    {
#if IS_DESKTOP
        ImGuiIO& io = ImGui::GetIO();

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

#endif // IS_DESKTOP
    }

    void ImGuiBackend::Shutdown()
    {
#if IS_DESKTOP
        ImGui_ImplSDL3_Shutdown();
        ImGui_ImplSDLGPU3_Shutdown();
        ImGui::DestroyContext();
#endif // IS_DESKTOP
    }

}
