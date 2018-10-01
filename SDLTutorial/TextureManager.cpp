#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL.h>
#include "LTexture.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	LTexture* pTexture = new LTexture(pRenderer);

	if (!pTexture->loadFromFile(fileName)) {
		std::cout << "Cannot load texture from file: " << fileName << std::endl;
		return true;
	}

	m_textureMap[id] = pTexture;
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	m_textureMap[id]->render(x, y);
}

void TextureManager::clearTextureMap()
{
	m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}