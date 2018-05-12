#pragma once
#include "ResourceManager.h"
#include "Sprite.h"
#include "Actor.h"
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
		void AddActorToUpdate(Actor* act);
		int Run();
		void Stop();
		void Cleanup();
	private:
		EngineRunner() {}
		
		void SetupScene();
		void CalculateDelta();
		void ProcessInput();
		void UpdateActors();
		void ProcessLogic();
		void RenderScene();
		void LoadResources();

		Uint64 _timeNow;
		Uint64 _lastTime;
		double _deltaTime;
		bool _isRunning;
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		std::vector<Sprite*> _backgroundTiles;
		std::vector<Actor*> _actorsToUpdate;
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;
	};
}