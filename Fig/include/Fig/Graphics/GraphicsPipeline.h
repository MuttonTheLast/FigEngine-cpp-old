#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsPipelineProps.h"
#include "SDL3/SDL_gpu.h"
namespace Fig
{
    class GraphicsPipeline
    {
    public:
        static GraphicsPipeline* Create(GraphicsDevice* device, GraphicsPipelineProps& props);

        ~GraphicsPipeline();
        
        void Bind(SDL_GPURenderPass* renderpass);

        void Release(GraphicsDevice* device);
        SDL_GPUGraphicsPipeline* GetHandle();
    private:
        GraphicsPipeline(GraphicsDevice* device, GraphicsPipelineProps& props);

        SDL_GPUGraphicsPipeline* m_Pipeline;
    };


};
