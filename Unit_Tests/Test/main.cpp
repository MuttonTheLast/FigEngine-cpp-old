#include "Fig/Graphics/Desktop/ShaderCross.h"
#include "Fig/Graphics/GraphicsDevice.h"
#include "Fig/Graphics/GraphicsPipeline.h"
#include "Fig/Graphics/GraphicsPipelineProps.h"
#include "Fig/Graphics/ShaderType.h"
#include "Fig/OS/File/FileSystem.h"
#include "Fig/OS/Window.h" 
#include <SDL3/SDL.h>
#include "Fig/Application/IApp.h"
#include "Fig/Utilities/Log/Logger.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_storage.h"
#include "quill/core/MacroMetadata.h"
#include <string>
#include <unistd.h>
#include <Fig/OS/EventHandler.h>
#include <vector>
#include <FigConfig.h>

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
        Shader* shader = Shader::Create(m_GraphicsDevice, shaderdata, ShaderType_Vertex, 0, 0, 0, 0);

        ShaderCross::SPIRVFromHLSL(data, shaderdata, Fig::ShaderType_Fragment);
        Shader* shader2 = Shader::Create(m_GraphicsDevice, shaderdata, ShaderType_Fragment, 0, 0, 0, 0);       
        data.clear();

        GraphicsPipelineProps pipelineProps{
            .VertexShader = shader,
            .FragmentShader = shader2,
            .PrimitiveType = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
            .TargerInfo = {
                .color_target_descriptions = (SDL_GPUColorTargetDescription[]){{
                    .format = SDL_GetGPUSwapchainTextureFormat(m_GraphicsDevice->GetHandle(), m_Window->GetHandle())
                }},
                .num_color_targets = 1,
            }
        };
        pipelineProps.RasterizerState.fill_mode = SDL_GPU_FILLMODE_FILL;
        pipeline = GraphicsPipeline::Create(m_GraphicsDevice, pipelineProps);

        m_GraphicsDevice->SetClearColor({0,1,1,1});
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


	// Inherited via IApp
	void Render(SDL_GPUCommandBuffer* cmdbuff, SDL_GPURenderPass* renderpass) override
	{
        
        pipeline->Bind(renderpass);
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
