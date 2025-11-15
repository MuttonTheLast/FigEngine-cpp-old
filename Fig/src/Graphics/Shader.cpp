#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/ShaderType.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include <Fig/Graphics/Shader.h>
#include <cstddef>
#include <cstring>
#include <vector>


namespace Fig
{
    
    Shader* Shader::Create(GraphicsDevice* gd,std::vector<Uint8>& data, ShaderType shaderType,
            Uint32 samplers, Uint32 storageTextures, Uint32 storageBuffers, Uint32 uniformBuffers,
            const char* entryPoint)
    {
        Shader* shader = new Shader(gd, data, shaderType, samplers, storageTextures,
                storageBuffers, uniformBuffers, entryPoint);

        return shader;
    }
    const char* Shader::GetDefaultEntry(ShaderType type)
    {
        const char* entry = "VSMain";

        switch (type) {
            case ShaderType_Vertex:
                entry = "VSMain";
                break;
            case ShaderType_Fragment:
                entry = "PSMain";
                break;
            case ShaderType_Compute:
                entry = "CSMain";
                break;
            default:
                entry = "main";
                break;
        }
        return entry;
    }
    Shader::Shader(GraphicsDevice* gd, std::vector<Uint8>& data, ShaderType shaderType,
            Uint32 samplers, Uint32 storageTextures, Uint32 storageBuffers, Uint32 uniformBuffers,
            const char* entryPoint)
    {

        const char* entry = entryPoint;
        if (entryPoint == NULL || strcmp(entry, "") == 0)
        {
            entry = Shader::GetDefaultEntry(shaderType);
        }
        
	    SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(gd->GetHandle());
        SDL_GPUShaderFormat format;
        if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV)
        {
            format = SDL_GPU_SHADERFORMAT_SPIRV;
        }
        else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL)
        {
            format = SDL_GPU_SHADERFORMAT_MSL;
        }
        else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL)
        {
            format = SDL_GPU_SHADERFORMAT_DXIL;
        }
        else
        {
            Logger::Error("Backend shader format is invalid.", "App");
            return;
        }
        SDL_GPUShaderCreateInfo createInfo
        {
            .code_size = data.size(),
            .code = data.data(),
            .entrypoint = entry,
            .format = format,
            .stage = (SDL_GPUShaderStage)shaderType,
            .num_samplers = samplers,
            .num_storage_textures = storageTextures,
            .num_storage_buffers = storageBuffers,
            .num_uniform_buffers = uniformBuffers

        };

        m_Shader = SDL_CreateGPUShader(gd->GetHandle(), &createInfo);
        if (m_Shader == NULL)
        {
            Logger::Error(SDL_GetError(), "App");
        }
    }

    SDL_GPUShader* Shader::GetHandle()
    {
        return m_Shader;
    }
}
