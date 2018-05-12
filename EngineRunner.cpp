#include "EngineRunner.h"

namespace Engine
{
	EngineRunner& EngineRunner::GetInstance()
	{
		static EngineRunner instance;

		return instance;
	}

	bool EngineRunner::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Logger::LogSDLError(std::cout, "SDL_Init");
			return false;
		}

		_window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_window == nullptr)
		{
			Logger::LogSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return false;
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == nullptr)
		{
			SDL_DestroyWindow(_window);
			Logger::LogSDLError(std::cout, "CreateRenderer");
			SDL_Quit();
			return false;
		}

		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		{
			Logger::LogSDLError(std::cout, "IMG_Init");
			SDL_Quit();
			return false;
		}

		ResourceManager::GetInstance().Init(_renderer);

		return true;
	}
	
	void EngineRunner::AddActorToUpdate(Actor* act)
	{
		_actorsToUpdate.emplace_back(act);
	}

	void EngineRunner::LoadResources()
	{
		ResourceManager::GetInstance().LoadTexturesFromFile("res\\textures.txt", _renderer);
		ResourceManager::GetInstance().LoadTextureAtlasFromJSON("res\\spritesheet.json", "res\\images\\spritesheet.png", _renderer);
	}

	void EngineRunner::SetupScene()
	{
		LoadResources();

		int tileWidth = ResourceManager::GetInstance().GetTextureResource("D_P_FULL")->GetWidth();
		int tileHeight = ResourceManager::GetInstance().GetTextureResource("D_P_FULL")->GetHeight();
		int xTiles = ceil((float)SCREEN_WIDTH / (float)tileWidth);
		int yTiles = ceil((float)SCREEN_HEIGHT / (float)tileHeight);
		_backgroundTiles = std::vector<Sprite*>();
		for (int i = 0; i < xTiles * yTiles; ++i)
		{
			int x = i % xTiles;
			int y = i / xTiles;
			_backgroundTiles.emplace_back(new Sprite(ResourceManager::GetInstance().GetTextureResource("D_P_FULL"), (float)(x * tileWidth), (float)(y * tileHeight), 1.0f, 1.0f));
		}

		Actor* testActor = new Actor(ResourceManager::GetInstance().GetTextureResource("MAN_GREEN"), 150, 150, 1.0f, 1.0f);

	}


	void EngineRunner::CalculateDelta()
	{
		_lastTime = _timeNow;
		_timeNow = SDL_GetTicks();

		
		_deltaTime = (_timeNow - _lastTime) / 1000.0f;
	}

	void EngineRunner::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				Stop();
			}
		}
	}

	void EngineRunner::UpdateActors()
	{
		for (std::vector<int>::size_type i = 0; i != _actorsToUpdate.size(); i++)
		{
			_actorsToUpdate[i]->Update(_deltaTime);
		}
	}

	void EngineRunner::ProcessLogic()
	{

	}

	void EngineRunner::RenderScene()
	{
		SDL_RenderClear(_renderer);
		for (std::vector<int>::size_type i = 0; i != _backgroundTiles.size(); i++) {
			_backgroundTiles[i]->Draw(_renderer);
		}
		for (std::vector<int>::size_type i = 0; i != _actorsToUpdate.size(); i++) {
			_actorsToUpdate[i]->Draw(_renderer);
		}
		SDL_RenderPresent(_renderer);
	}

	int EngineRunner::Run()
	{
		_isRunning = true;

		SetupScene();

		_timeNow = SDL_GetTicks();
		_lastTime = 0;

		while (_isRunning)
		{
			CalculateDelta();
			ProcessInput();
			UpdateActors();
			ProcessLogic();
			RenderScene();
		}

		Cleanup();

		return 0;
	}

	void EngineRunner::Stop()
	{
		_isRunning = false;
	}

	void EngineRunner::Cleanup()
	{
		ResourceManager::GetInstance().CleanupResources();
		for (std::vector<int>::size_type i = 0; i != _actorsToUpdate.size(); i++)
		{
			delete _actorsToUpdate[i];
		}
		_actorsToUpdate.clear();
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		IMG_Quit();
		SDL_Quit();
	}
}