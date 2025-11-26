#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"
namespace Fig
{
    class GraphicsPipeline
    {
    public:

        GraphicsPipeline(const GraphicsDevice* device, SDL_GPUGraphicsPipelineCreateInfo& props);
        ~GraphicsPipeline();
        
        void Bind(SDL_GPURenderPass* renderpass);

        void Release(GraphicsDevice* device);
        SDL_GPUGraphicsPipeline* GetHandle();
    private:

        SDL_GPUGraphicsPipeline* m_Pipeline;
    };


};
