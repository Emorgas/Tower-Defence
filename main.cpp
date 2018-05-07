#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "ResourceManager.h"
#include "TextureResource.h"
#include "Sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool quit = false;

SDL_Window* window;
SDL_Renderer* renderer;

ResourceManager* resourceManager;

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return false;
	}

	window = SDL_CreateWindow("Tower Defence", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		logSDLError(std::cout, "CreateRenderer");
		SDL_Quit();
		return false;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return false;
	}

	resourceManager = new ResourceManager(renderer);

	return true;
}

void loadResources()
{
	resourceManager->LoadTexturesFromFile("res\\textures.txt", renderer);
	resourceManager->LoadTextureAtlasFromJSON("res\\spritesheet.json", "res\\images\\spritesheet.png", renderer);
}

int main(int, char**)
{
	if (!init())
	{
		return 1;
	}

	loadResources();

	int tileWidth = resourceManager->GetTextureResource("D_P_HTSPT_A")->GetWidth();
	int tileHeight = resourceManager->GetTextureResource("D_P_HTSPT_A")->GetHeight();
	int xTiles = ceil((float)SCREEN_WIDTH / (float)tileWidth);
	int yTiles = ceil((float)SCREEN_HEIGHT / (float)tileHeight);
	std::vector<Sprite*> backgroundTiles = std::vector<Sprite*>();
	for (int i = 0; i < xTiles * yTiles; ++i)
	{
		int x = i % xTiles;
		int y = i / xTiles;
		backgroundTiles.emplace_back(new Sprite(resourceManager->GetTextureResource("D_P_HTSPT_A"), (float)(x * tileWidth), (float)(y * tileHeight), 1.0f, 1.0f));
	}
	SDL_Point moveVector;
	moveVector.x = 1;
	moveVector.y = 1;

	while (!quit)
	{

		// Input loop
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_RenderClear(renderer);
		for (std::vector<int>::size_type i = 0; i != backgroundTiles.size(); i++) {
			backgroundTiles[i]->Draw(renderer);
		}
		SDL_RenderPresent(renderer);
	}

	delete resourceManager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}