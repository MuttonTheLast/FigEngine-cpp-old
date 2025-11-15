#pragma once

#include <FigConfig.h>

#if IS_DESKTOP

#include <SDL3_shadercross/SDL_shadercross.h>
#include "Fig/Graphics/GraphicsBackend.h"
#include "Fig/Graphics/ShaderType.h"
#include <vector>
#include <string>

namespace Fig
{
    enum ShaderSource
    {
        ShaderSource_None = -1,
        ShaderSource_HLSL,
        ShaderSource_SPIRV,
    };
    class ShaderCross
    {
    public:
        static bool Init();

        static void Shutdown();

        static bool FromSource(std::vector<Uint8>& sourceCode, std::vector<Uint8>& buffer,
            ShaderType type,GraphicsBackend backend, ShaderSource sourceType = ShaderSource_HLSL,
            std::string_view includeDir = "");

        static bool FromHLSL(std::vector<Uint8>& sourceCode, std::vector<Uint8>& buffer,
                ShaderType type, GraphicsBackend backend, std::string_view includeDir = "");

        static bool FromSPIRV(std::vector<Uint8>& sourceCode, std::vector<Uint8>& buffer,
                ShaderType type,GraphicsBackend backend, std::string_view includeDir = "");

        static bool SPIRVFromHLSL(std::vector<Uint8>& sourceCode, std::vector<Uint8>& buffer,
                ShaderType type, std::string_view includeDir = "");

        static bool DXILFromHLSL(std::vector<Uint8>& sourceCode, std::vector<Uint8>& buffer,
                ShaderType type, std::string_view includeDir = "");

        static bool DXILFromSPIRV(std::vector<Uint8>& sourceCode, std::vector<Uint8>& buffer,
                ShaderType type);
        
        // SetDefaultIncludePath relative to executable
        static void SetDefaultIncludePath(std::string_view path);
    private:
        // TODO: replace all m_ for statics
        static std::string m_IncludePath;
        
        static void MakeIncludeStr(std::string_view& includeDir, std::string& include);
        
    };
}

#endif // IS_DESKTOP
