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
	Sprite *img = new Sprite(resourceManager->GetTextureResource("image"), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f, 1.0f);
	float tileWidth = resourceManager->GetTextureResource("background")->GetWidth();
	float tileHeight = resourceManager->GetTextureResource("background")->GetHeight();
	int xTiles = SCREEN_WIDTH / tileWidth;
	int yTiles = SCREEN_HEIGHT / tileHeight;
	std::vector<Sprite*> backgroundTiles = std::vector<Sprite*>();
	for (int i = 0; i < xTiles * yTiles; ++i)
	{
		int x = i % xTiles;
		int y = i / xTiles;
		backgroundTiles.emplace_back(new Sprite(resourceManager->GetTextureResource("background"), (float)(x * tileWidth), (float)(y * tileHeight), 1.0f, 1.0f));
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

		// Logic
		if (img->GetPosition().x > SCREEN_WIDTH)
		{
			moveVector.x = -1;
		}
		else if (img->GetPosition().x < 0)
		{
			moveVector.x = 1;
		}
		if (img->GetPosition().y > SCREEN_HEIGHT)
		{
			moveVector.y = -1;
		}
		else if (img->GetPosition().y < 0)
		{
			moveVector.y = 1;
		}
		
		img->MovePos(moveVector);

		SDL_RenderClear(renderer);
		for (std::vector<int>::size_type i = 0; i != backgroundTiles.size(); i++) {
			backgroundTiles[i]->Draw(renderer);
		}
		img->Draw(renderer);
		SDL_RenderPresent(renderer);
	}

	delete resourceManager;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}