#ifndef THEGAME_H_INCLUDED
#define THEGAME_H_INCLUDED


#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Ingame.h"

class Game
{
private:
    /****************************
    Basic stuff
    ****************************/
    sf::Vector2i mouseposition; //a vector variable for the cursor's position

    sf::Event event;

    enum Game_state{Menu = 1,Maingame = 2};
    Game_state game_state;

    /****************************
    Game operating
    ****************************/
    Game_data game;

    Game_Menu menu;

    Ingame ingame;

    /****************************
    Graphics
    ****************************/

    sf::RenderWindow window;

    /*********************************
    Functions
    *********************************/
    void getMousePosition();
    bool isMouseinGame();

public:
    Game();

    void start();
};

#endif // THEGAME_H_INCLUDED
