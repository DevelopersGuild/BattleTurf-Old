#ifndef THEGAME_H_INCLUDED
#define THEGAME_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Box.h"
#include "Player.h"

/****************************
Game settings, will be changed after we create the menu.
****************************/
const int NUM_WALL = 8;         //number of wall
const int NUM_PLAYER = 4;       //number of player, must be less or equals to than 4
const int NUM_BOX_WIDTH = 6;    //the width of the map
const int NUM_BOX_HEIGHT = 6;   //the height of the map
const int NUM_SCORE_EACH_PLAYER = ((NUM_BOX_WIDTH * NUM_BOX_HEIGHT) - NUM_WALL) / NUM_PLAYER;       //the number of score box that each player can put in the game
const int BOX_SIZE = 55;        //the size of the box
const int INTERFACE_SIZE = NUM_BOX_WIDTH * BOX_SIZE / 2; //the width of the interface

class Game
{
private:
    /****************************
    Basic stuff
    ****************************/
    sf::Vector2i mouseposition; //a vector variable for the cursor's position

    /****************************
    Game operating
    ****************************/
    Player player[NUM_PLAYER];  //declare players
    Player *player_order[NUM_PLAYER];
    int current_active_player;  //determine who moves.
    int turn_passed;            //how many turn has passed

    Box box[NUM_BOX_WIDTH][NUM_BOX_HEIGHT]; //the map
    Box *currentbox;            //a pointer for marking the box that the cursor located.
    Box *lastbox;               //a pointer that remember the last 'currentbox'.

    /****************************
    Graphics
    ****************************/
    sf::Font font;                                  //the font of the score
    sf::Text Graphing_score[NUM_BOX_WIDTH][NUM_BOX_HEIGHT];  //score[][]is the score for graphing only, it doesn't change the game.
    sf::RectangleShape GraphingRect1;                    //the background of the current scorebox
    sf::Text Graphing_scorebox;                            //the text of the current scorebox
    sf::Text Graphing_player_score[NUM_PLAYER];

    sf::RenderWindow window;

    /*********************************
    Functions
    *********************************/
    void Event_MouseMoved();
    void Event_MouseLeftClicked();
    void Graphic_updateAll();               //refresh graphics
    void Graphic_int_ToString(int value, sf::Text &targettext);     //convery integer to sf::Text
    void Graphic_Show_Cursor_CurrentBox(Box *currentbox, Box *lastbox);
    void HandleEvent(sf::Event &event);
    void Mech_Calculate_Score();
    void Mech_Check_adjacent(sf::Vector2i mouseposition,Box *currentbox, Box box[][NUM_BOX_HEIGHT],sf::Text score[][NUM_BOX_HEIGHT]);
    void Mech_NextPlayer();
    void Mech_Reset_Player_Scores();
    void Mech_Rearrange_order();
    void Mech_Set_Score_Pool();
    void Mech_Set_Wall();

    int Mech_Find_winner();

    bool isMouseinGame();

public:
    Game();

    void start();
};

#endif // THEGAME_H_INCLUDED
