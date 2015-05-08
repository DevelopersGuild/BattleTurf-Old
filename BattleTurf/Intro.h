#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Ingame.h"



/****************************
The intro animation when opening the game
*****************************/
class Intro
{
private:
    Game_data *ptrsetting;
    sf::RenderWindow *ptrwindow;
    sf::Font *ptrfont;

    sf::RectangleShape introBackground;
public:
    Intro();

    void Init(sf::RenderWindow *window, Game_data *setting, sf::Font *font);

    void Play();

};

#endif // INTRO_H_INCLUDED
