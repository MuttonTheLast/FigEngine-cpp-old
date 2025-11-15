
#include <Fig/Graphics/Desktop/ShaderCross.h>

#if IS_DESKTOP

#include <string_view>
#include "SDL3_shadercross/SDL_shadercross.h"
#include "Fig/Graphics/GraphicsBackend.h"
#include "Fig/Graphics/ShaderType.h"
#include "Fig/Graphics/Shader.h"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_stdinc.h"
#include <cstddef>
#include <string>

namespace Fig{

    std::string ShaderCross::m_IncludePath;

    bool ShaderCross::Init()
    {
        if (!SDL_ShaderCross_Init()) {
            return false;
        }
        m_IncludePath = std::string(SDL_GetBasePath()) + "/assets/";
        
        return true;
    }

    void ShaderCross::Shutdown()
    {

        SDL_ShaderCross_Quit();
    }

    // TODO: add more shader types
    
    bool ShaderCross::FromSource(std::vector<Uint8> &source, std::vector<Uint8> &buffer,
            ShaderType type, GraphicsBackend backend, ShaderSource sourceType,
            std::string_view includeDir)
    {
        switch (sourceType) {
            case ShaderSource_HLSL:
                return ShaderCross::FromHLSL(source, buffer, type, backend, includeDir);
            case ShaderSource_SPIRV:
                return ShaderCross::FromSPIRV(source, buffer, type, backend, includeDir);
            default:
                return false;
        }
    }

    bool ShaderCross::FromHLSL(std::vector<Uint8> &source, std::vector<Uint8> &buffer,
            ShaderType type, GraphicsBackend backend, std::string_view includeDir)
    {
        switch (backend) {
            case GraphicsBackend_D3D12:
                return ShaderCross::DXILFromHLSL(source, buffer, type, includeDir);
            case GraphicsBackend_VULKAN:
                return ShaderCross::SPIRVFromHLSL(source, buffer, type, includeDir);
            default:
                return false;
        }
    }

    bool ShaderCross::FromSPIRV(std::vector<Uint8> &source, std::vector<Uint8> &buffer, 
            ShaderType type, GraphicsBackend backend, std::string_view includeDir)
    {
        switch (backend) {
            case GraphicsBackend_D3D12:
                return ShaderCross::SPIRVFromHLSL(source, buffer, type, includeDir);
            case GraphicsBackend_VULKAN:
                return ShaderCross::SPIRVFromHLSL(source, buffer, type, includeDir);
            default:
                return false;
        }
    }

    bool ShaderCross::DXILFromHLSL(std::vector<Uint8> &source, std::vector<Uint8> &buffer,
            ShaderType type,  std::string_view includeDir)
    {
        size_t size;

        std::string include;
        MakeIncludeStr(includeDir, include);

        SDL_ShaderCross_HLSL_Info info{
            .source = (const char*)source.data(),
            .entrypoint = Shader::GetDefaultEntry(type),
            .include_dir = include.c_str(),
            .shader_stage = (SDL_ShaderCross_ShaderStage)type,
        };

        void* data = SDL_ShaderCross_CompileDXILFromHLSL(&info, &size);
        if (data == NULL)
        {
            SDL_free(data);
            return false;
        }
        buffer.resize(size);
        memcpy(buffer.data(), data, size); // copy compiled bytes into vector
        SDL_free(data);
        return true;
    }

    bool ShaderCross::SPIRVFromHLSL(std::vector<Uint8> &source, std::vector<Uint8> &buffer, 
            ShaderType type, std::string_view includeDir)
    {
        size_t size;

        std::string include;
        MakeIncludeStr(includeDir, include);

        SDL_ShaderCross_HLSL_Info info{
            .source = (const char*)source.data(),
            .entrypoint = Shader::GetDefaultEntry(type),
            .include_dir = include.c_str(),
            .shader_stage = (SDL_ShaderCross_ShaderStage)type,
        };
        void* data = SDL_ShaderCross_CompileSPIRVFromHLSL(&info, &size);
        if (data == NULL)
        {
            SDL_free(data);
            return false;
        }
        buffer.resize(size);
        memcpy(buffer.data(), data, size); // copy compiled bytes into vector
        SDL_free(data);
        return true;
    }
    bool ShaderCross::DXILFromSPIRV(std::vector<Uint8> &source, std::vector<Uint8> &buffer, 
            ShaderType type)
    {
        size_t size;
        SDL_ShaderCross_SPIRV_Info info{
            .bytecode = source.data(),
            .bytecode_size = source.size(),
            .entrypoint = Shader::GetDefaultEntry(type),
            .shader_stage = (SDL_ShaderCross_ShaderStage)type,
        };
        void* data = SDL_ShaderCross_CompileDXILFromSPIRV(&info, &size);
        buffer.resize(size);
        memcpy(buffer.data(), data, size);
        SDL_free(data);
        return true;
    }

    void ShaderCross::SetDefaultIncludePath(std::string_view path)
    {
        
        m_IncludePath = std::string(SDL_GetBasePath());
        m_IncludePath += path; 
    }

    void ShaderCross::MakeIncludeStr(std::string_view& includeDir, std::string& include)
    {
        if (includeDir.empty()) {
            include = m_IncludePath;
        } else {
            include = SDL_GetBasePath();   // one allocation
            include += includeDir;         // efficient append, no temporary
        }
    }
}

#endif

