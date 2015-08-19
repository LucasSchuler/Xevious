/*
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 *  XEVIOUS REMAKE
 *  ANTONIO KINDERMANN E LUCAS SCHULER
 *
 */

#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include "GameState.h"
#include "Sprite.h"
#include "InputManager.h"
#include <tmx/MapLoader.h>
#include <string>

class PlayState : public cgf::GameState
{
    private:
    float panY;
    float panX;

    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    // Implement Singleton Pattern
    static PlayState* instance()
    {
        return &m_PlayState;
    }

    protected:

    PlayState() {}

    private:

    static PlayState m_PlayState;

    enum { RIGHT=0, LEFT, UP, DOWN };
    std::string walkStates[4];
    int currentDir;

    int x, y;
    int dirx, diry;

    cgf::Sprite player;
    cgf::Sprite terrestres1[9];
    cgf::Sprite terrestres2[8];
    cgf::Sprite terrestres1sp[9];
    cgf::Sprite terrestres2sp[8];
    cgf::Sprite chefe;

    cgf::Sprite tirosIniReto[100];
    cgf::Sprite tirosIniDiag[100];

    cgf::Sprite tirosNave[100];

    sf::Clock clockCriaTirosNave; // starts the clock
    sf::Clock clockCriaTiros; // starts the clock

    sf::RenderWindow* screen;
    cgf::InputManager* im;

    tmx::MapLoader* map;

    sf::Font font;
    sf::Text text;
    sf::Text placar;
    sf::Text acabou;

    void inimigos();

    void movTiros();

    void criaTiroNave();

    void colisaoTiros();

    void criaTiroDiagInimigo(float x, float y);

    void criaTiroRetoInimigo(float x, float y);

    // Centers the camera on the player position
    void centerMapOnPlayer();

    // Checks collision between a sprite and a map layer
    bool checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj);

    // get a cell GID from the map (x and y in world coords)
    sf::Uint16 getCellFromMap(uint8_t layernum, float x, float y);
};

#endif
