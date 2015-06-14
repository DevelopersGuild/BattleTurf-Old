#ifndef THEGAME_H_INCLUDED
#define THEGAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Menu.h"
#include "Ingame.h"
#include "Intro.h"

class Game
{
private:
    /****************************
    Basic stuff
    ****************************/
    sf::Vector2i mouseposition; //a vector variable for the cursor's position
    sf::Event event;

    enum Game_state_num{Start = 0,Menu = 1,Maingame = 2};
    Game_state_num game_state;

    /****************************
    Game operating
    ****************************/
    Game_data gamedata;
    Game_Menu *menu;
    Ingame *ingame;
    Intro *intro;
    /****************************
    Graphics
    ****************************/
    sf::VideoMode videoMode;
    sf::RenderWindow window;
    sf::Font *font;

    /*********************************
    Functions
    *********************************/
    void getMousePosition();
    bool isMouseingame();
    bool isMouseinWindow();

    /*********************************
    Networking
    *********************************/
    sf::TcpSocket* socket;

public:
    Game();

    void start();
};

#endif // THEGAME_H_INCLUDED
