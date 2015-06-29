/*
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 *  XEVIOUS REMAKE
 *  ANTONIO KINDERMANN E LUCAS SCHULER
 *
 */
#include <windows.h>
#include <iostream>
#include <cmath>
#include "Game.h"
#include "PlayState.h"
#include "InputManager.h"

PlayState PlayState::m_PlayState;

int vidaNave = 7;
int inimigos = 0;

using namespace std;

void PlayState::init(){

    //Inicializar os inimigos terrestres e fixos
    int i;
    for(i = 0 ; i < 100 ; i++){
        tirosIniReto[i].setPosition(-1,-1);
        tirosIniDiag[i].setPosition(-1,-1);
        tirosNave[i].setPosition(-1,-1);
    }

    terrestres1[0].setPosition(203,1144);
    terrestres1[1].setPosition(203,1180);
    terrestres1[2].setPosition(203,1271);
    terrestres1[3].setPosition(183,408);
    terrestres1[4].setPosition(228,457);
    terrestres1[5].setPosition(274,507);
    terrestres1[6].setPosition(172,1500);
    terrestres1[7].setPosition(240,2005);
    terrestres1[8].setPosition(170,2655);

    terrestres2[0].setPosition(55,455);
    terrestres2[1].setPosition(251,482);
    terrestres2[2].setPosition(205,433);
    terrestres2[3].setPosition(171,763);
    terrestres2[4].setPosition(172,1526);
    terrestres2[5].setPosition(218,1980);
    terrestres2[6].setPosition(207,2104);
    terrestres2[7].setPosition(170,2261);

    //chefe.load("data/img/enemy.png");
    chefe.setPosition(183,304);

    //Inicializar os inimigos moveis



    panY = 2880;
    panX = 160;

    if (!font.loadFromFile("data/fonts/arial.ttf")) {
        cout << "Cannot load arial.ttf font!" << endl;
        exit(1);
    }

    placar.setFont(font);
    placar.setString("Vidas: "+vidaNave);//" Vidas:"+vidaNave +" - Inimigos Mortos:"+inimigos);
    placar.setCharacterSize(20); // in pixels
    placar.setColor(sf::Color::Yellow);
    placar.setStyle(sf::Text::Bold);
    placar.setPosition(panX,panY);

    acabou.setFont(font);
    acabou.setCharacterSize(30); // in pixels
    acabou.setColor(sf::Color::Blue);
    acabou.setStyle(sf::Text::Bold);
    //acabou.setString("        Parabéns!\n\n Você foi o vencedor\n\n\n      Vá para cima \n até o fim do cenário");
    //acabou.setPosition(panX-150, panY-100);

    map = new tmx::MapLoader("data/maps");       // all maps/tiles will be read from data/maps
    // map->AddSearchPath("data/maps/tilesets"); // e.g.: adding more search paths for tilesets
    map->Load("scene_1.tmx");

    player.load("data/img/nave.png");
    player.setPosition(160,3150);

    im = cgf::InputManager::instance();

    im->addKeyInput("left", sf::Keyboard::Left);
    im->addKeyInput("right", sf::Keyboard::Right);
    im->addKeyInput("up", sf::Keyboard::Up);
    im->addKeyInput("down", sf::Keyboard::Down);
    im->addKeyInput("quit", sf::Keyboard::Escape);
    im->addKeyInput("stats", sf::Keyboard::S);
    im->addMouseInput("rightclick", sf::Mouse::Right);
    im->addKeyInput("space", sf::Keyboard::Space);

    cout << "PlayState: Init" << endl;
}

void PlayState::criaTiroDiagInimigo(float x, float y){
    int i;
    for(i = 0 ; i < 100 ; i++){
        if(tirosIniDiag[i].getPosition().y == -1){
            tirosIniDiag[i].load("data/img/tiro.png");
            tirosIniDiag[i].setScale(0.4,0.4);
            tirosIniDiag[i].setPosition(x-3,y-3);
            tirosIniDiag[i+1].load("data/img/tiro.png");
            tirosIniDiag[i+1].setScale(0.4,0.4);
            tirosIniDiag[i+1].setPosition(x-3,y-3);
            return;
        }
    }
}

void PlayState::criaTiroRetoInimigo(float x, float y){
    int i;
    for(i = 0 ; i < 100 ; i++){
        if(tirosIniReto[i].getPosition().y == -1){
            tirosIniReto[i].load("data/img/tiro.png");
            tirosIniReto[i].setScale(0.4,0.4);
            tirosIniReto[i].setPosition(x-3,y-3);
            return;
        }
    }
}

void PlayState::inimigos(){
    // criando tiros a cada 2 segundos e zerando o clock.
    sf::Time elapsed = clockCriaTiros.getElapsedTime();
    if(elapsed.asSeconds() < 2) return;
    else clockCriaTiros.restart();
    //para cada tipo de inimigo:
    int i;
    sf::Vector2f pos;
    for(i = 0; i < 9; i++){
        pos = terrestres1[i].getPosition();
        // há inimigos na janela atual
        if(pos.y < panY+300 && pos.y > panY-400 && pos.y != 0 && pos.x != 0){
            //disparar
            criaTiroDiagInimigo(pos.x, pos.y);
        }
    }
    for(i = 0; i < 9; i++){
        pos = terrestres2[i].getPosition();
        // há inimigos na janela atual
        if(pos.y < panY+300 && pos.y > panY-400 && pos.y != 0 && pos.x != 0){
            //disparar
            criaTiroRetoInimigo(pos.x, pos.y);
        }
    }
    // disparar a cada 1 ou 2 segundos
}

void PlayState::movTiros(){
    int i, dirX = 0, dirY = 0;
    sf::Vector2f pos;
    // movendo tiros diagonais do inimigo
    for(i = 0 ; i < 100 ; i++){
        pos = tirosIniDiag[i].getPosition();
        if(pos.y != -1){
            if(i%2 == 0){ //par -> direita
                //dirX = 1;
                //dirY = 3;
                tirosIniDiag[i].setPosition(pos.x+1,pos.y+3);
            }
            else{ //impar -> esquerda
                //dirX = -1;
                //dirY = 3;
                tirosIniDiag[i].setPosition(pos.x-1,pos.y+3);
            }
            //tirosIniDiag[i].setXspeed(100*dirX);
            //tirosIniDiag[i].setYspeed(100*dirY);

            if(pos.x > 320 || pos.x < -32 || pos.y < panY-320 || pos.y > panY+320 ){ // remover o tiro que saiu da tela.
                tirosIniDiag[i].setPosition(-1,-1);
            }
        }

    }
    // movendo tiros retos do inimigo
    for(i = 0 ; i < 100 ; i++){
        pos = tirosIniReto[i].getPosition();
        //cout<<"tiro:";
        //cout<<pos.y;
        if(pos.y != -1){
            tirosIniReto[i].setPosition(pos.x,pos.y+3);

            if(pos.x > 320 || pos.x < -32 || pos.y < panY-320 || pos.y > panY+320 ){ // remover o tiro que saiu da tela.
                tirosIniReto[i].setPosition(-1,-1);
            }
        }

    }
    // movendo tiros da nave
    for(i = 0 ; i < 100 ; i++){
        pos = tirosNave[i].getPosition();
        if(pos.y != -1){
            tirosNave[i].setPosition(pos.x,pos.y-7);

            if(pos.x > 320 || pos.x < -32 || pos.y < panY-320 || pos.y > panY+320 ){ // remover o tiro que saiu da tela.
                tirosNave[i].setPosition(-1,-1);
            }
        }

    }
}

void PlayState::criaTiroNave(){
    // criando tiros a cada 2 segundos e zerando o clock.
    sf::Time elapsed = clockCriaTirosNave.getElapsedTime();
    if(elapsed.asSeconds() < 0.1) return;
    else clockCriaTirosNave.restart();

    sf::Vector2f pos = player.getPosition();
    int i;
    for(i = 0 ; i < 100 ; i++){
        if(tirosNave[i].getPosition().y == -1){
            tirosNave[i].load("data/img/tiro.png");
            tirosNave[i].setScale(0.4,0.4);
            tirosNave[i].setPosition(pos.x+12,pos.y-6);
            return;
        }
    }
}

void PlayState::cleanup(){
    delete map;
    cout << "PlayState: Clean" << endl;
}

void PlayState::pause(){
    cout << "PlayState: Paused" << endl;
}

void PlayState::resume(){
    cout << "PlayState: Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game){
    screen = game->getScreen();
    sf::View view = screen->getView(); // gets the view
    sf::Event event;

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
    }

    dirx = diry = 0;
    int newDir = currentDir;

    if(im->testEvent("space")){
        criaTiroNave();
    }

    if(im->testEvent("left")) {
        sf::Vector2f pos = player.getPosition();
        if(pos.x>0){
            dirx = -2;
            newDir = LEFT;
        }
    }

    if(im->testEvent("right")) {
        sf::Vector2f pos = player.getPosition();
        if(pos.x<350){
            dirx = 2;
            newDir = RIGHT;
        }
    }

    if(im->testEvent("up")) {
        sf::Vector2f pos = player.getPosition();
        if(pos.y <= 0){
            exit(0);
        }
        if(pos.y >= (panY-315)) {
            diry = -2;
            newDir = UP;
        }
    }

    if(im->testEvent("down")) {
        sf::Vector2f pos = player.getPosition();
        if((pos.y - panY)<290){
            diry = 2;
            newDir = DOWN;
        }
    }

    if(im->testEvent("quit") || im->testEvent("rightclick"))
        game->quit();

    if(im->testEvent("stats"))
        game->toggleStats();




    if(im->testEvent("zoomin")) {
        view.zoom(1.01);
        screen->setView(view);
    }
    else if(im->testEvent("zoomout")) {
        view.zoom(0.99);
        screen->setView(view);
    }

    if(dirx == 0 && diry == 0) {
        player.pause();
    }
    else {
        if(currentDir != newDir) {
            player.setAnimation(walkStates[newDir]);
            currentDir = newDir;
        }
        player.play();
    }

    player.setXspeed(100*dirx);
    player.setYspeed(100*diry);
}

void PlayState::update(cgf::Game* game){
    screen = game->getScreen();

    // CHECAR A COLISAO COM RESPECTIVO LAYER [0,1,2,...]
    checkCollision(0, game, &player);

    // player.update(game->getUpdateInterval();
    centerMapOnPlayer();

    // cria tiros inimigos se ele aparecer na tela.
    inimigos();

    // move os tiros na tela
    movTiros();

    //Verifica se algum tiro acertou o seu alvo
    colisaoTiros();
}

void PlayState::draw(cgf::Game* game){
    screen = game->getScreen();
    map->Draw(*screen);          // draw all layers
//    map->Draw(*screen, 1);     // draw only the second layer
    screen->draw(player);
    int i;
    for(i = 0 ; i < 100 ; i++){
        if(tirosIniReto[i].getPosition().y > 0) screen->draw(tirosIniReto[i]);
        if(tirosIniDiag[i].getPosition().y > 0) screen->draw(tirosIniDiag[i]);
        if(tirosNave[i].getPosition().y > 0) screen->draw(tirosNave[i]);
    }
    screen->draw(placar);
    screen->draw(acabou);
}

void PlayState::centerMapOnPlayer(){
    sf::View view = screen->getView();
    sf::Vector2u mapsize = map->GetMapSize();
    sf::Vector2f viewsize = view.getSize();
    viewsize.x /= 2;
    viewsize.y /= 2;
    sf::Vector2f pos = player.getPosition();

    if(panY>330){
        panY-=1;
        if((pos.y - panY)>290){
             player.setPosition(pos.x,pos.y-1);
        }
    }

    sf::Vector2f center(panX,panY);
    view.setCenter(center);
    screen->setView(view);
}

void PlayState::colisaoTiros(){
    sf::Vector2f pos = player.getPosition();

    //Colisoes contra a nave
    for(int i=0; i<100; i++){
        sf::Vector2f posTiroReto = tirosIniReto[i].getPosition();
        sf::Vector2f posTiroDiag = tirosIniDiag[i].getPosition();
        //Verifica se algum tiro reto acertou
        if(posTiroReto.x>=pos.x-10
           && posTiroReto.x<=pos.x+30
           && posTiroReto.y>=pos.y-30
           && posTiroReto.y<=pos.y+30){
            vidaNave--;
            tirosIniReto[i].setPosition(-1,-1);
            //cout<<"acertou Reto";
        }
        // Verifica se algum tiro diag acertou
        if(posTiroDiag.x>=pos.x-10
           && posTiroDiag.x<=pos.x+30
           && posTiroDiag.y>=pos.y-40
           && posTiroDiag.y<=pos.y+30){
            vidaNave--;
            tirosIniDiag[i].setPosition(-1,-1);
            //cout<<"acertou Diag";
        }
    }

    //Verifica se as vidas acabaram
    if(vidaNave==0){
        cout<<"perdeu";
        acabou.setColor(sf::Color::Red);
        acabou.setString("    Você foi derrotado.\n\n\n   pressione ESC");
        acabou.setPosition(panX-150, panY-100);
    }

    //Colisoes contra os inimigos
    for(int i=0; i<100; i++){
        sf::Vector2f posTiroNave = tirosNave[i].getPosition();
        //Verificar p/ todos inimigos terrestres1
        for(int ter1=0;ter1<9;ter1++){
            sf::Vector2f posTerrestre = terrestres1[ter1].getPosition();
            if(posTiroNave.x<=posTerrestre.x+20
               && posTiroNave.x>=posTerrestre.x-20
               && posTiroNave.y>=posTerrestre.y-40
               && posTiroNave.y<=posTerrestre.y+30
               ){
              tirosNave[i].setPosition(-1,-1);      // eliminando o tiro
              terrestres1[ter1].setPosition(-1,-1); // eliminando o inimigo
               // cout<<"acertou Inimigo";
            }
        }
        //Verificar p/ todos inimigos terrestres2
        for(int ter2=0;ter2<8;ter2++){
            sf::Vector2f posTerrestre = terrestres2[ter2].getPosition();
            if(posTiroNave.x<=posTerrestre.x+20
               && posTiroNave.x>=posTerrestre.x-20
               && posTiroNave.y>=posTerrestre.y-40
               && posTiroNave.y<=posTerrestre.y+30
               ){
                tirosNave[i].setPosition(-1,-1);        // eliminando o tiro
                terrestres2[ter2].setPosition(-1,-1);   // eliminando o inimigo
               // cout<<"acertou Inimigo";
            }
        }
        //Verificar se acertou o chefe
        if(posTiroNave.x<=chefe.getPosition().x+30
           && posTiroNave.x>=chefe.getPosition().x-30
           && posTiroNave.y>=chefe.getPosition().y-40
           && posTiroNave.y<=chefe.getPosition().y+30
           ){
            tirosNave[i].setPosition(-1,-1);// eliminando o tiro
            chefe.setPosition(-1,-1);       // eliminando o inimigo
            acabou.setString("        Parabéns!\n\n Você foi o vencedor\n\n\n      Vá para cima \n até o fim do cenário");
            acabou.setPosition(panX-150, panY-100);
        }
    }
}

bool PlayState::checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj){
    int i, x1, x2, y1, y2;
    bool bump = false;

    // Get the limits of the map
    sf::Vector2u mapsize = map->GetMapSize();
    // Get the width and height of a single tile
    sf::Vector2u tilesize = map->GetMapTileSize();

    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    mapsize.x--;
    mapsize.y--;

    // Get the height and width of the object (in this case, 100% of a tile)
    sf::Vector2u objsize = obj->getSize();
    objsize.x *= obj->getScale().x;
    objsize.y *= obj->getScale().y;

    float px = obj->getPosition().x;
    float py = obj->getPosition().y;

    double deltaTime = game->getUpdateInterval();

    sf::Vector2f offset(obj->getXspeed()/1000 * deltaTime, obj->getYspeed()/1000 * deltaTime);

    float vx = offset.x;
    float vy = offset.y;

    //cout << "px,py: " << px << " " << py << endl;

    //cout << "tilesize " << tilesize.x << " " << tilesize.y << endl;
    //cout << "mapsize " << mapsize.x << " " << mapsize.y << endl;

    // Test the horizontal movement first
    i = objsize.y > tilesize.y ? tilesize.y : objsize.y;

    for (;;)
    {
        x1 = (px + vx) / tilesize.x;
        x2 = (px + vx + objsize.x - 1) / tilesize.x;

        y1 = (py) / tilesize.y;
        y2 = (py + i - 1) / tilesize.y;

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vx > 0)
            {
                // Trying to move right

                int upRight   = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (upRight || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    px = x2 * tilesize.x;
                    px -= objsize.x;// + 1;
                    vx = 0;
                    bump = true;
                }
            }

            else if (vx < 0)
            {
                // Trying to move left

                int upLeft   = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int downLeft = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                if (upLeft || downLeft)
                {
                    // Place the player as close to the solid tile as possible
                    px = (x1+1) * tilesize.x;
                    vx = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.y) // Checked player height with all tiles ?
        {
            break;
        }

        i += tilesize.y; // done, check next tile upwards

        if (i > objsize.y)
        {
            i = objsize.y;
        }
    }

    // Now test the vertical movement

    i = objsize.x > tilesize.x ? tilesize.x : objsize.x;

    for (;;)
    {
        x1 = (px / tilesize.x);
        x2 = ((px + i-1) / tilesize.x);

        y1 = ((py + vy) / tilesize.y);
        y2 = ((py + vy + objsize.y-1) / tilesize.y);

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vy > 0)
            {
                // Trying to move down
                int downLeft  = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (downLeft || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = y2 * tilesize.y;
                    py -= objsize.y;
                    vy = 0;
                    bump = true;
                }
            }

            else if (vy < 0)
            {
                // Trying to move up

                int upLeft  = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int upRight = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                if (upLeft || upRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = (y1 + 1) * tilesize.y;
                    vy = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.x)
        {
            break;
        }

        i += tilesize.x; // done, check next tile to the right

        if (i > objsize.x)
        {
            i = objsize.x;
        }
    }

    // Now apply the movement and animation

    obj->setPosition(px+vx,py+vy);
    px = obj->getPosition().x;
    py = obj->getPosition().y;

    obj->update(deltaTime, false); // only update animation

    // Check collision with edges of map
    if (px < 0)
        obj->setPosition(px,py);
    else if (px + objsize.x >= mapsize.x * tilesize.x)
        obj->setPosition(mapsize.x*tilesize.x - objsize.x - 1,py);

    if(py < 0)
        obj->setPosition(px,0);
    else if(py + objsize.y >= mapsize.y * tilesize.y)
        obj->setPosition(px, mapsize.y*tilesize.y - objsize.y - 1);

    return bump;
}

// Get a cell GID from the map (x and y in global coords)
sf::Uint16 PlayState::getCellFromMap(uint8_t layernum, float x, float y){
    auto layers = map->GetLayers();
    tmx::MapLayer& layer = layers[layernum];
    sf::Vector2u mapsize = map->GetMapSize();
    sf::Vector2u tilesize = map->GetMapTileSize();
    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    int col = floor(x / tilesize.x);
    int row = floor(y / tilesize.y);

    return layer.tiles[row*mapsize.x + col].gid;
}
