#pragma once
#include "ResourceManager.h"
#include "Sprite.h"
#include "TextureResource.h"
#include "Logger.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
namespace Engine
{
	class EngineRunner
	{
	public:
		static EngineRunner& GetInstance();

		EngineRunner(EngineRunner const&) = delete;
		void operator=(EngineRunner const&) = delete;

		bool Init();
		int Run();
		void Stop();
		void Cleanup();
	private:
		EngineRunner() {}
		
		void SetupScene();
		void ProcessInput();
		void RenderScene();
		void LoadResources();

		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		ResourceManager* resourceManager;
		std::vector<Sprite*> backgroundTiles;
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;
	};
}