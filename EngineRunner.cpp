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

		window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			Logger::LogSDLError(std::cout, "CreateWindow");
			SDL_Quit();
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr)
		{
			SDL_DestroyWindow(window);
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

		resourceManager = new ResourceManager(renderer);

		return true;
	}

	void EngineRunner::LoadResources()
	{
		resourceManager->LoadTexturesFromFile("res\\textures.txt", renderer);
		resourceManager->LoadTextureAtlasFromJSON("res\\spritesheet.json", "res\\images\\spritesheet.png", renderer);
	}

	void EngineRunner::SetupScene()
	{
		LoadResources();

		int tileWidth = resourceManager->GetTextureResource("D_P_HTSPT_A")->GetWidth();
		int tileHeight = resourceManager->GetTextureResource("D_P_HTSPT_A")->GetHeight();
		int xTiles = ceil((float)SCREEN_WIDTH / (float)tileWidth);
		int yTiles = ceil((float)SCREEN_HEIGHT / (float)tileHeight);
		backgroundTiles = std::vector<Sprite*>();
		for (int i = 0; i < xTiles * yTiles; ++i)
		{
			int x = i % xTiles;
			int y = i / xTiles;
			backgroundTiles.emplace_back(new Sprite(resourceManager->GetTextureResource("D_P_HTSPT_A"), (float)(x * tileWidth), (float)(y * tileHeight), 1.0f, 1.0f));
		}
		SDL_Point moveVector;
		moveVector.x = 1;
		moveVector.y = 1;

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

	void EngineRunner::RenderScene()
	{
		SDL_RenderClear(renderer);
		for (std::vector<int>::size_type i = 0; i != backgroundTiles.size(); i++) {
			backgroundTiles[i]->Draw(renderer);
		}
		SDL_RenderPresent(renderer);
	}

	int EngineRunner::Run()
	{
		isRunning = true;

		SetupScene();

		while (isRunning)
		{
			ProcessInput();
			RenderScene();
		}

		Cleanup();

		return 0;
	}

	void EngineRunner::Stop()
	{
		isRunning = false;
	}

	void EngineRunner::Cleanup()
	{
		delete resourceManager;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
	}
}