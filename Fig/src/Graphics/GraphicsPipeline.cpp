#include "Fig/Graphics/GraphicsPipeline.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsPipelineProps.h"
#include "SDL3/SDL_gpu.h"

namespace Fig
{
    GraphicsPipeline* GraphicsPipeline::Create(GraphicsDevice* device,GraphicsPipelineProps& props)
    {
        GraphicsPipeline* pipeline = new GraphicsPipeline(device, props);

        return pipeline;
    }
    
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

    GraphicsPipeline::GraphicsPipeline(GraphicsDevice* device, GraphicsPipelineProps& props)
    {
        SDL_GPUGraphicsPipelineCreateInfo info
        {
            .vertex_shader = props.VertexShader->GetHandle(),
            .fragment_shader = props.FragmentShader->GetHandle(),
            .primitive_type = props.PrimitiveType,
            .rasterizer_state = props.RasterizerState,
            .target_info = props.TargerInfo
        };
        m_Pipeline = SDL_CreateGPUGraphicsPipeline(device->GetHandle(), &info);
    }

};
