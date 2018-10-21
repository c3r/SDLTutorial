#include "TextureManager.h"
#include "LTexture.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id,
        SDL_Renderer* pRenderer) {
        LTexture* pTexture = new LTexture(pRenderer);

        if (!pTexture->loadFromFile(fileName)) {
                std::cout << "Cannot load texture from file: " << fileName << std::endl;
                return true;
        }

        m_textureMap[id] = pTexture;
        return false;
}

void TextureManager::draw(std::string textureId, int x, int y, SDL_Rect* clip) {
        m_textureMap[textureId]->render(x, y, clip);
}

void TextureManager::clearTextureMap() { m_textureMap.clear(); }

void TextureManager::clearFromTextureMap(std::string id) {
        m_textureMap.erase(id);
}

TextureManager::TextureManager() { return; }
