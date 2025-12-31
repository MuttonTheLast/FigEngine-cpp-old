
#include "Fig/Application/UI/ImGuiBackend.h"
#include "Fig/Graphics/Desktop/ShaderCross.h"
#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include <Fig/Graphics/Shader.h>
#include "Fig/Graphics/Sampler.h"
#include "Fig/Graphics/ShaderType.h"
#include "Fig/Graphics/Texture/Texture.h"
#include "Fig/Graphics/TransferBuffer.h"
#include "Fig/Graphics/Vertex/IVertexType.h"
#include "Fig/Graphics/Vertex/VertexElementFormat.h"
#include "Fig/OS/File/FileSystem.h"
#include "Fig/OS/Window.h" 
#include <SDL3/SDL.h>
#include "Fig/Application/IApp.h"
#include "Fig/Utilities/GLMath.h"
#include "Fig/Utilities/ImGui/imgui.h"
#include "Fig/Utilities/Image/ImgManager.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "quill/core/MacroMetadata.h"
#include <iostream>
#include <iterator>
#include <string>
#include <Fig/OS/EventHandler.h>
#include <vector>
#include <FigConfig.h>
#include <Fig/Graphics/GraphicsPipeline.h>

using namespace Fig;

class Game : public IApp
{
public:
	Game(std::string appName, std::string companyName, WindowProps prop, bool debug)
		:IApp(appName, companyName, prop, debug)
	{
           
	}
private:
    GraphicsPipeline* pipeline;

    GraphicsBuffer* VBO;
    GraphicsBuffer* IBO;

    SDL_Surface* surface;
    Texture* texture;

    SDL_GPUSampler* sampler;
	// Inherited via IApp
	bool Init() override
	{
        EventHandler::SetSizeChangeCallback( [this](int width, int height) 
                { return SizeChangeCallback(width, height); });
        
        std::vector<Uint8> data;
        if (FileSystem::ReadFile("assets/TQuad.vert.hlsl", data))
        {
            Logger::Info("ReadFile", "App", false);
            Logger::Info(std::string((char*)data.data()), "App");
        }

        std::vector<Uint8> shaderdata;
        ShaderCross::FromSource(data, shaderdata, Fig::ShaderType_Vertex, GetBackend());
        Shader shader = Shader(m_GraphicsDevice, shaderdata, ShaderType_Vertex, 0, 0, 0, 0);

        ShaderCross::FromSource(data, shaderdata, Fig::ShaderType_Fragment, GetBackend());
        Shader shader2 = Shader(m_GraphicsDevice, shaderdata, ShaderType_Fragment, 1, 0, 0, 0);       
        data.clear();

        if (!FileSystem::ReadFile("assets/image.png", data))
        {
            Logger::Error("Failed to load assets/image.png", "App");
        }
        surface = ImgManager::SurfaceFromRawData(data);
        data.clear();
        
        texture = new Texture(m_GraphicsDevice, SDL_GPU_TEXTURETYPE_2D,SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
                surface->w, surface->h);

        sampler = Sampler::CreatePointClamp(m_GraphicsDevice);

        SDL_GPUGraphicsPipelineCreateInfo pipelineProps{
            .vertex_shader = shader.GetHandle(),
            .fragment_shader = shader2.GetHandle(),
            .vertex_input_state = SDL_GPUVertexInputState{
                .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[]){
                    SDL_GPUVertexBufferDescription{
                        .slot = 0,
                        .pitch = sizeof(PositionUVVertex),
                        .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                        .instance_step_rate = 0,
                    }
                },
                .num_vertex_buffers = 1,
                .vertex_attributes = (SDL_GPUVertexAttribute[]){
                    SDL_GPUVertexAttribute{
                        .location = 0,
                        .buffer_slot = 0,
                        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                        .offset = 0,
                    },
                    SDL_GPUVertexAttribute{
                        .location = 1,
                        .buffer_slot = 0,
                        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
                        .offset = sizeof(Vector3),
                    },
                },
                .num_vertex_attributes = 2,
            },
            
            .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
            .target_info = {
                .color_target_descriptions = (SDL_GPUColorTargetDescription[]){{
                    .format = SDL_GetGPUSwapchainTextureFormat(m_GraphicsDevice->GetHandle(),
                            m_Window->GetHandle())
                }},
                .num_color_targets = 1,
            },
        };
        pipelineProps.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;
        pipeline = new GraphicsPipeline(m_GraphicsDevice, pipelineProps);

        // m_GraphicsDevice->SetClearColor({0,1,1,1});
        
        Logger::Info(std::to_string(sizeof(PositionUVVertex)), "App");
        
        VBO = new GraphicsBuffer(m_GraphicsDevice, SDL_GPU_BUFFERUSAGE_VERTEX, 
                sizeof(PositionUVVertex) * 4);

        IBO = new GraphicsBuffer(m_GraphicsDevice, SDL_GPU_BUFFERUSAGE_INDEX, 
                sizeof(Uint16) * 6);
        
        TransferBuffer tb(m_GraphicsDevice, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
                sizeof(PositionUVVertex) * 4 + sizeof(Uint16) * 6);
        std::cout << texture->GetSizeInBytes() << "\n";
        std::cout << surface->pitch * surface->h << "\n";

        PositionUVVertex* transferData = (PositionUVVertex*) tb.Map();
    

        
        transferData[0] = (PositionUVVertex) { Vector3(-0.5,-0.5,0), Vector2(0,1) };
        transferData[1] = (PositionUVVertex) {  Vector3(-0.5, 0.5, 0), Vector2(0,0) };
        transferData[2] = (PositionUVVertex) {  Vector3(0.5, 0.5,0), Vector2(1,0) };
        transferData[3] = (PositionUVVertex) {  Vector3(0.5, -0.5,0), Vector2(1, 1) };

        Uint16* indexData = (Uint16*) &transferData[4];
        indexData[0] = 0;
        indexData[1] = 1;
        indexData[2] = 2;
        indexData[3] = 0;
        indexData[4] = 2;
        indexData[5] = 3;
    
	    tb.Unmap();

        
        TransferBuffer ttb(m_GraphicsDevice, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
                texture->GetSizeInBytes());
        Uint8* textureTransferPtr = (Uint8*)ttb.Map();
        SDL_memcpy(textureTransferPtr, surface->pixels, 
                surface->pitch * surface->h);
        ttb.Unmap();
        
        
        // Upload the transfer data to the GPU resources
        SDL_GPUCommandBuffer* uploadCmdBuf = SDL_AcquireGPUCommandBuffer(m_GraphicsDevice->GetHandle());
        SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuf);
        

        tb.Upload(copyPass, 0, VBO, 0, sizeof(PositionUVVertex) * 4);
        tb.Upload(copyPass, sizeof(PositionUVVertex) * 4, IBO, 0, sizeof(Uint16) * 6);
        ttb.Upload(copyPass, 0, texture, false);

        SDL_EndGPUCopyPass(copyPass);
        SDL_SubmitGPUCommandBuffer(uploadCmdBuf);
        tb.Dispose();
        ttb.Dispose();

		return true;
	}

    bool SizeChangeCallback(int width, int height)
    {
        
        return true;
    }

	void FixedUpdate(double delta) override
	{
	}
	double updateCount = 0;
	void Update(double delta) override
	{
		updateCount += delta;
	}

    void ImGuiUpdate(double delta) override
    {
        ImGui::ShowDemoWindow();
        
    }

    void PreRender(SDL_GPUCommandBuffer* cmdbuff) override
    {
    }
	// Inherited via IApp
	void Render(SDL_GPUCommandBuffer* cmdbuff, SDL_GPURenderPass* renderpass) override
	{
        
        SDL_GPUBufferBinding vbb
        {
            .buffer = VBO->GetHandle(),
            .offset = 0
        };

        SDL_GPUBufferBinding ibb
        {
            .buffer = IBO->GetHandle(),
            .offset = 0
        };
        pipeline->Bind(renderpass);
        SDL_BindGPUVertexBuffers(renderpass, 0, &vbb, 1);
        SDL_BindGPUIndexBuffer(renderpass ,&ibb, SDL_GPU_INDEXELEMENTSIZE_16BIT);
        SDL_GPUTextureSamplerBinding sampBind
        { 
            .texture = texture->GetHandle(),
            .sampler = sampler
        };
		SDL_BindGPUFragmentSamplers(renderpass, 0, &sampBind, 1);
        SDL_DrawGPUIndexedPrimitives(renderpass, 6, 1, 0, 0, 0);
	}

public:

};


int main()
{
	WindowProps props("test");
    props.Resizable = true;

	Game* game = new Game("DefaultGame", "Fig", props, true);
	game->Run();
    return 0;
}
