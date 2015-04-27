/*
 *  TextureManager.cpp
 *  framework
 *
 *  Created by Marcelo Cohen on 07/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include "TextureManager.h"
#include <iostream>

namespace cgf
{

using namespace std;

TextureManager TextureManager::m_TextureManager;

TextureManager::TextureManager()
{
    defaultImageDir = "data";
}

TextureManager::~TextureManager()
{
    //dtor
    cout << "~TextureManager: deleting " << imgs.size() << endl;
    map<string,sf::Texture*>::iterator it = imgs.begin();
    while(it != imgs.end())
    {
        sf::Texture* tex = (*it).second;
        delete tex;
        it++;
    }
}

sf::Texture* TextureManager::findTexture(char* nomeArq)
{
    if(imgs.find(nomeArq) == imgs.end()) {
        cout << "New texture: " << nomeArq;
        sf::Texture* tex = new sf::Texture();
        if(!tex->loadFromFile(nomeArq))
            return NULL;
        cout << " (" << tex->getSize().x << " x " << tex->getSize().y << ")" << endl;
        imgs[nomeArq] = tex;
        tex->setSmooth(true);
        return tex;
    }
    // Return texture id
    cout << "Existing texture: " << nomeArq << " (" << imgs[nomeArq]->getSize().x << " x " << imgs[nomeArq]->getSize().y << ")" << endl;
    return imgs[nomeArq];
}

void TextureManager::setDefaultImageDir(char* dir)
{
    defaultImageDir = dir;
}

void TextureManager::releaseTexture(char* nomeArq)
{
    if(imgs.find(nomeArq) != imgs.end())
    {
        sf::Texture* tex = imgs[nomeArq];
        imgs.erase(nomeArq);
        delete tex;
        //glDeleteTextures(1, &tex);
    }
}

} // namespace cgf
