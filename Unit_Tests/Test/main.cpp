
#include "Fig/Application/UI/ImGuiBackend.h"
#include "Fig/Graphics/Desktop/ShaderCross.h"
#include "Fig/Graphics/GraphicsBuffer.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include <Fig/Graphics/Shader.h>
#include "Fig/Graphics/ShaderType.h"
#include "Fig/Graphics/TransferBuffer.h"
#include "Fig/Graphics/Vertex/IVertexType.h"
#include "Fig/Graphics/Vertex/VertexElementFormat.h"
#include "Fig/OS/File/FileSystem.h"
#include "Fig/OS/Window.h" 
#include <SDL3/SDL.h>
#include "Fig/Application/IApp.h"
#include "Fig/Utilities/GLMath.h"
#include "Fig/Utilities/ImGui/imgui.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include "quill/core/MacroMetadata.h"
#include <iostream>
#include <iterator>
#include <string>
#include <unistd.h>
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
	// Inherited via IApp
	bool Init() override
	{
        EventHandler::SetSizeChangeCallback( [this](int width, int height) 
                { return SizeChangeCallback(width, height); });
        
        std::vector<Uint8> data;
        if (FileSystem::ReadFile("assets/cube.vert.hlsl", data))
        {
            Logger::Info("ReadFile", "App", false);
            Logger::Info(std::string((char*)data.data()), "App");
        }

        std::vector<Uint8> shaderdata;
        ShaderCross::SPIRVFromHLSL(data, shaderdata, Fig::ShaderType_Vertex);
        Shader shader = Shader(m_GraphicsDevice, shaderdata, ShaderType_Vertex, 0, 0, 0, 0);

        ShaderCross::SPIRVFromHLSL(data, shaderdata, Fig::ShaderType_Fragment);
        Shader shader2 = Shader(m_GraphicsDevice, shaderdata, ShaderType_Fragment, 0, 0, 0, 0);       
        data.clear();
        
        SDL_GPUGraphicsPipelineCreateInfo pipelineProps{
            .vertex_shader = shader.GetHandle(),
            .fragment_shader = shader2.GetHandle(),
            .vertex_input_state = SDL_GPUVertexInputState{
                .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[]){
                    SDL_GPUVertexBufferDescription{
                        .slot = 0,
                        .pitch = sizeof(PositionColorVertex),
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
                        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
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
        
        PositionColorVertex pcv{};
        pcv.Position = Vector3(1,2,3);
        pcv.Color = Vector3(1,0,0);
        
        Logger::Info(std::to_string(sizeof(PositionColorVertex)), "App");
        
        VBO = new GraphicsBuffer(m_GraphicsDevice, SDL_GPU_BUFFERUSAGE_VERTEX, 
                sizeof(PositionColorVertex) * 3);
        
        TransferBuffer tb(m_GraphicsDevice, SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
                sizeof(PositionColorVertex) * 3);

        PositionColorVertex* transferData = (PositionColorVertex*) tb.Map(m_GraphicsDevice);
    

        
        transferData[0] = (PositionColorVertex) { Vector3(-0.5,-0.5,0), Vector3(1,0,0) };
        transferData[1] = (PositionColorVertex) {  Vector3(0, 0.5, 0), Vector3(0,1,0) };
        transferData[2] = (PositionColorVertex) {  Vector3(0.5,-0.5,0), Vector3(0,0,1) };
    
	    tb.Unmap(m_GraphicsDevice);

        
        // Upload the transfer data to the GPU resources
        SDL_GPUCommandBuffer* uploadCmdBuf = SDL_AcquireGPUCommandBuffer(m_GraphicsDevice->GetHandle());
        SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuf);

        tb.Upload(copyPass, 0, VBO, 0, sizeof(PositionColorVertex) * 3);
            

        SDL_EndGPUCopyPass(copyPass);
        SDL_SubmitGPUCommandBuffer(uploadCmdBuf);
        tb.Release(m_GraphicsDevice);    

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
        
        SDL_GPUBufferBinding bb
        {
            .buffer = VBO->GetHandle(),
            .offset = 0
        };
        pipeline->Bind(renderpass);
        SDL_BindGPUVertexBuffers(renderpass, 0, &bb, 1);
        SDL_DrawGPUPrimitives(renderpass, 3, 1, 0, 0);
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
