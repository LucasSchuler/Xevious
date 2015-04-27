/*
 *  Game.h
 *  Main game class
 *
 *  Created by Marcelo Cohen on 05/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#ifndef CGF_GAME_H
#define CGF_GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stack>
#include "ClockHUD.h"

namespace cgf
{

class GameState;

class Game
{
    public:

        Game(int minFrameRate=15, int maxFrameRate=20);
        void init(const char* title, int width, int height, bool fullscreen);
        void handleEvents();
        void changeState(GameState* state);
        void pushState(GameState* state);
        void popState();
        void update();
        void draw();
        void clean();
        bool isRunning() { return running; }
        void quit()    { running = false; }
        sf::RenderWindow* getScreen() { return screen; }
        static void printAttributes();
        double getUpdateInterval() { return updateInterval; }

        void toggleStats() { showStats = !showStats; }
        void enableStats() { showStats = true; }
        void disabeStats() { showStats = false; }

    private:

        sf::RenderWindow* screen;
        sf::View originalView;
        bool running;
        bool fullscreen;
        bool showStats;

        int bpp; // bits per pixel (screen colour depth)
        std::stack<GameState*> states;
        // Fixed interval time-based animation
        sf::Clock gameClock;
        int minFrameRate;
        int maxFrameRate;
        double updateInterval;
        double maxCyclesPerFrame;
        double lastFrameTime;
        double cyclesLeftOver;

        sf::Font font;
        sfx::FrameClock clock;
        ClockHUD* hud;
        // Audio engine
//        irrklang::ISoundEngine* audioEngine;
};

} // namespace cgf

#endif // CGF_GAME
