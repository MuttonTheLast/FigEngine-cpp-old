#include "Fig/Graphics/CommandBuffer.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"

namespace Fig
{
    Texture* CommandBuffer::AcquireSwapchainTexture(Uint32* width, Uint32* height)
    {
        SDL_GPUTexture* texture;
        Uint32 w,h;
        SDL_AcquireGPUSwapchainTexture(m_CmdBuf, m_GraphicsDevice->GetWindow()->GetHandle()
                , &texture, &w, &h);
        
    }
}
