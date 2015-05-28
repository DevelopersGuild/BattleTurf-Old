#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED
#include <SFML/Graphics.hpp>
struct Game_data
{
    int NUM_WALL;         //number of wall
    int NUM_PLAYER;       //number of player, must be less or equals to than 4
    int NUM_BOX_WIDTH;    //the width of the map
    int NUM_BOX_HEIGHT;   //the height of the map
    int NUM_SCORE_EACH_PLAYER;      //the number of score box that each player can put in the game
    int BOX_SIZE;        //the size of the box
    int INTERFACE_SIZE; //the width of the interface
};

class Game_State
{
protected:
    sf::RenderWindow *ptrwindow;
    const sf::Font *ptrfont;
    const sf::Vector2i *ptrMousePosition;
    const Game_data *ptrgameSetting;
    const sf::Event *ptrevent;
public:
    virtual ~Game_State(){;}
};

#endif // GAME_STATE_H_INCLUDED
