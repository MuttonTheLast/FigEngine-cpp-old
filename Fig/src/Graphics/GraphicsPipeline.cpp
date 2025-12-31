#include "Fig/Graphics/GraphicsPipeline.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_gpu.h"
#include <cstddef>

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

    void GraphicsPipeline::Dispose()
    {
        if (m_Disposed)
            return;

        if (m_Pipeline != NULL)
        {
            SDL_ReleaseGPUGraphicsPipeline(m_GraphicsDevice->GetHandle(), m_Pipeline);
            m_Pipeline = NULL;
        }
        m_Disposed = true;
    }

    GraphicsPipeline::GraphicsPipeline(const GraphicsDevice* device,
            SDL_GPUGraphicsPipelineCreateInfo& props)
        :GraphicsResource((GraphicsDevice*)device)
    {
        m_Pipeline = SDL_CreateGPUGraphicsPipeline(device->GetHandle(), &props);
    }
    
    GraphicsPipeline::~GraphicsPipeline()
    {
        Dispose();
    }
};
