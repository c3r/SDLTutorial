#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>
#include "LTexture.h"

class TextureManager {
public:
        static TextureManager* Instance() {
                if (s_pInstance == 0) {
                        s_pInstance = new TextureManager();
                        return s_pInstance;
                }
                return s_pInstance;
        }

        bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
        bool loadText(TTF_Font* pFont, std::string id, SDL_Renderer* pRenderer);

        void clearTextureMap();
        void clearFromTextureMap(std::string id);

        void draw(std::string id, int x, int y, SDL_Rect* pClip = NULL);

        std::map<std::string, LTexture*> getTextureMap() { return m_textureMap; }

private:
        TextureManager();
        ~TextureManager();

        TextureManager(const TextureManager&);
        TextureManager& operator=(const TextureManager&);

        std::map<std::string, LTexture*> m_textureMap;
        static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;
