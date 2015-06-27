/*
 *  XEVIOUS REMAKE
 *  ANTONIO KINDERMANN E LUCAS SCHULER
 *
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Game.h"
#include "PlayState.h"

int main(int argc, char **argv)
{
    cgf::Game game(5,30);

	game.init("XEVIOUS REMAKE",320,640,false);

    game.changeState(PlayState::instance());

    sf::Music music;
    if (!music.openFromFile("data/audio/Game_Music.wav"))
        return -1; // error
    music.setLoop(true);
    music.play();

	while(game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.draw();
	}

	// cleanup the engine
	game.clean();

    return 0;
}
