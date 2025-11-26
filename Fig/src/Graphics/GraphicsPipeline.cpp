#include "Fig/Graphics/GraphicsPipeline.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "SDL3/SDL_gpu.h"

namespace Fig
{
    
    SDL_GPUGraphicsPipeline* GraphicsPipeline::GetHandle()
    {
        return m_Pipeline;
    }
    
    void GraphicsPipeline::Bind(SDL_GPURenderPass* renderpass)
    {
        SDL_BindGPUGraphicsPipeline(renderpass, m_Pipeline);
    }

    void GraphicsPipeline::Release(GraphicsDevice* device)
    {
        if (m_Pipeline != NULL)
        {
            SDL_ReleaseGPUGraphicsPipeline(device->GetHandle(), m_Pipeline);
        }
    }

    GraphicsPipeline::GraphicsPipeline(const GraphicsDevice* device,
            SDL_GPUGraphicsPipelineCreateInfo& props)
    {
        m_Pipeline = SDL_CreateGPUGraphicsPipeline(device->GetHandle(), &props);
    }

};
