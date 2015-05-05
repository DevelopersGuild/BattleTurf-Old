#ifndef INGAME_H_INCLUDED
#define INGAME_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <SFMl/Graphics.hpp>
#include "Box.h"
#include "Player.h"
#include "vector"

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

class Ingame
{
private:
    /******************
    Game data
    ******************/
    sf::RenderWindow *ptrwindow;
    const sf::Event *ptrevent;
    const sf::Vector2i *ptrMousePosition;
    const Game_data *ptrgameSetting;

    /******************
    Game operation
    ******************/
    Player *player;
    Player **player_order;
    int current_active_player;  //determine who moves.
    int turn_passed;            //how many turn has passed

    Box box[11][11]; //the map

    Box *currentbox;            //a pointer for marking the box that the cursor located.
    Box *lastbox;               //a pointer that remember the last 'currentbox'.

    /******************
    Graphics
    ******************/
    sf::Font font;                                  //the font of the score
    //sf::Text Graphing_score[11][11];  //score[][]is the score for graphing only, it doesn't change the game.
    sf::RectangleShape GraphingRect1;                    //the background of the current scorebox
    sf::Text Graphing_scorebox;                            //the text of the current scorebox
    sf::Text *Graphing_player_score;

    /******************
    Functions
    ******************/
    void Event_MouseMoved();

    void Event_MouseLeftClicked();
    void Mech_NextPlayer();

    void Mech_Set_Score_Pool();
    void Mech_Set_Wall();
    void Mech_Check_adjacent();
    void Mech_Reset_Player_Scores();
    void Mech_Calculate_Score();
    int Mech_Find_winner();
    void Mech_Rearrange_order();

    void Graphic_int_ToString(int value, sf::Text &targettext);

public:
    Ingame();
    ~Ingame();

    void Init(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *gameSetting);

    void update();

    void HandleEvent();

    void Show_Cursor_Box();

};

#endif // INGAME_H_INCLUDED
