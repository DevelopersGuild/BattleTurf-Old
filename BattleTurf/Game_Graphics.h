#ifndef GAME_GRAPHICS_H_INCLUDED
#define GAME_GRAPHICS_H_INCLUDED

#include "Graphic.h"

class Game_Graphics : public Graphic
{
    private:
    /* The graphic elements in the game
    sf::Font font;                                  //the font of the score
    sf::Text Graphing_score[NUM_BOX_WIDTH][NUM_BOX_HEIGHT];  //score[][]is the score for graphing only, it doesn't change the game.
    sf::RectangleShape GraphingRect1;                    //the background of the current scorebox
    sf::Text Graphing_scorebox;                            //the text of the current scorebox
    sf::Text Graphing_player_score[NUM_PLAYER];             //shows player's score
    */
    public:
    //constructor
    Game_Graphics();

    //show all things in the game on the window
    void show(sf::RenderWindow &window);

    //show particular element. Do we need it?
    //void show_Graphing_score(sf::RenderWindow &window);
    //void show_GraphingRect1(sf::RenderWindow &window);
    //...

    //hide all things in the game on the window
    void hide(sf::RenderWindow &window);

    //hide particular element. Do we need it?
    //void hide_Graphing_score(sf::RenderWindow &window);
    //void hide_GraphingRect1(sf::RenderWindow &window);
    //...

};

Game_Graphics::Game_Graphics()
{

}

void Game_Graphics::show(sf::RenderWindow &window)
{

}

void Game_Graphics::hide(sf::RenderWindow &window)
{

}

#endif // GAME_GRAPHICS_H_INCLUDED
