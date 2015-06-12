#ifndef INGAME_H_INCLUDED
#define INGAME_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Player.h"
#include "vector"
#include "Game_State.h"

class Ingame : public Game_State
{
private:
    /******************
    Game data
    ******************/

    /******************
    Game operation
    ******************/
    Player *player;
    Player **player_order;
    int current_active_player;  //determine who moves.
    int turn_passed;            //how many turn has passed

    Box **box; //the map

    Box *currentbox;            //a pointer for marking the box that the cursor located.
    Box *lastbox;               //a pointer that remember the last 'currentbox'.

    /******************
    Graphics
    ******************/
    //sf::Font *ptrfont;                                  //the font of the score
    //sf::Text Graphing_score[11][11];  //score[][]is the score for graphing only, it doesn't change the game.
    sf::RectangleShape background;
    sf::RectangleShape GraphingRect1;                    //the background of the current scorebox
    sf::Text Graphing_scorebox;                            //the text of the current scorebox
    sf::Text *Graphing_player_score;
    sf::Texture scoreBoxTexture;
    
    //box texture
    sf::Texture box_texture;
    sf::Texture box_texture_wall;
    
    sf::Texture focusTexture;
    
    sf::Texture texture;

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
    bool isMouseinGame();

public:
    Ingame();
    Ingame(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *gameSetting, sf::Font *font);
    ~Ingame();

    void update();

    void HandleEvent();

    void Show_Cursor_Box();

};

#endif // INGAME_H_INCLUDED
