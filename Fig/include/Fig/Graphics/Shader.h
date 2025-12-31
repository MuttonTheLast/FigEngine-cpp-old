#pragma once
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsResource.h"
#include "Fig/Graphics/ShaderType.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include <SDL3/SDL.h>
#include <vector>


namespace Fig {
    class Shader : public GraphicsResource
    {
    public:
        Shader(GraphicsDevice* gd, std::vector<Uint8>& data,
                ShaderType shaderType, Uint32 samplers,
                Uint32 storageTextures, Uint32 storageBuffers, Uint32 uniformBuffers,
                const char* entryPoint = "");
        
        

        static const char* GetDefaultEntry(ShaderType type);
        SDL_GPUShader* GetHandle();
 
        void Dispose() override;

        ~Shader();
    private:
        SDL_GPUShader* m_Shader;

    };
}
