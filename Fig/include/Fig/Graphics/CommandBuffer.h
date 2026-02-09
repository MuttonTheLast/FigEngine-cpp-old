#pragma once

#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsPipeline.h"
#include "Fig/Graphics/Texture/Texture.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include <vector>
namespace Fig
{
    class CommandBuffer
    {
    public:
        CommandBuffer(GraphicsDevice* gd)
            :m_GraphicsDevice(gd)
        {
            m_CmdBuf = SDL_AcquireGPUCommandBuffer(gd->GetHandle());
        }
        ~CommandBuffer();

        Texture* AcquireSwapchainTexture(Uint32* width = NULL, Uint32* height = NULL);

        Texture* WaitAndAcquireSwapchainTexture(Uint32* width = NULL, Uint32* height = NULL);

        SDL_GPURenderPass* BeginRenderPass(std::vector<SDL_GPUColorTargetInfo>& colorTargetInfo,
                SDL_GPUDepthStencilTargetInfo* depthStencilInfo);
        void EndRenderPass();
        void Submit();
        void Close();

        void BindPipeline(GraphicsPipeline* pipeline);
        void SetViewport(SDL_GPUViewport* viewport);
        void BindVertexBuffer(Uint32 firstSlot, std::vector<SDL_GPUBufferBinding>& bindings);
        void BindVertexSamplers(Uint32 firstSlot,
                std::vector<SDL_GPUTextureSamplerBinding>& bindings);

        void Draw(Uint32 numVertices, Uint32 numInstances,
                Uint32 firstVertex, Uint32 firstInstance);

        void Draw(GraphicsBuffer* buffer, Uint32 offset, Uint32 count);

        void DrawIndexed(GraphicsBuffer* buffer, Uint32 offset, Uint32 count);



    private:
        SDL_GPUCommandBuffer* m_CmdBuf;
        GraphicsDevice* m_GraphicsDevice;
        SDL_GPURenderPass* SDL_GPURenderPass;
    };
}
