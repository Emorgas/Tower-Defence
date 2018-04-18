#include <iostream>
#include <ostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "ResourceManager.h"
#include "TextureResource.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

bool quit = false;

SDL_Window* window;
SDL_Renderer* renderer;

ResourceManager* resourceManager;

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = h;
	dst.w = w;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
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

int main(int, char**)
{
	if (!init())
	{
		return 1;
	}

	std::string imagePath = "res\\images\\background.png";
	resourceManager->AddTextureResource(imagePath, "background", renderer);
	imagePath = "res\\images\\image.png";
	resourceManager->AddTextureResource(imagePath, "image", renderer);

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

		int xTiles = SCREEN_WIDTH / TILE_SIZE;
		int yTiles = SCREEN_HEIGHT / TILE_SIZE;

		for (int i = 0; i < xTiles * yTiles; ++i)
		{
			int x = i % xTiles;
			int y = i / xTiles;
			renderTexture(resourceManager->GetTextureResource("background")->GetTexture(), renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}

		TextureResource* res = resourceManager->GetTextureResource("image");
		int x = SCREEN_WIDTH / 2 - res->GetWidth() / 2;
		int y = SCREEN_HEIGHT / 2 - res->GetHeight() / 2;
		renderTexture(res->GetTexture(), renderer, x, y);

		SDL_RenderPresent(renderer);
	}

	delete resourceManager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}