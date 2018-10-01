#ifndef __LTEXTURE__
#define __LTEXTURE__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class LTexture
{
public:

	LTexture(SDL_Renderer* renderer);
	~LTexture();

	bool loadFromFile(std::string path);
	void setColor(uint8_t red, uint8_t green, uint8_t blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(uint8_t alpha);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	//Image dimensions
	int mWidth;
	int mHeight;
};
#endif