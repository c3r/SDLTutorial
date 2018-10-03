#include "LTexture.h"
#include <iostream>

LTexture::LTexture(SDL_Renderer* pRenderer)
{
	renderer = pRenderer;
	texture = NULL;
	width = 0;
	height = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) 
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	width = loadedSurface->w;
	height = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
	texture = newTexture;
	return texture != NULL;
}

void LTexture::free()
{
	if (texture == NULL)
		return;

	SDL_DestroyTexture(texture);
	texture = NULL;
	width = 0;
	height = 0;
}

void LTexture::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(texture, blending);
}

void LTexture::setAlpha(uint8_t alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip , double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() { return width; }

int LTexture::getHeight() { return height; }
