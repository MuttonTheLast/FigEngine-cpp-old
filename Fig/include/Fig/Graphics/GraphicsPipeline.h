#pragma once

#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsResource.h"
#include "SDL3/SDL_gpu.h"
namespace Fig
{
    class GraphicsPipeline : public GraphicsResource
    {
    public:

        GraphicsPipeline(const GraphicsDevice* device, SDL_GPUGraphicsPipelineCreateInfo& props);
        ~GraphicsPipeline();
        
        void Bind(SDL_GPURenderPass* renderpass);

        void Dispose() override;

        SDL_GPUGraphicsPipeline* GetHandle();
    private:

        SDL_GPUGraphicsPipeline* m_Pipeline;
    };


};
