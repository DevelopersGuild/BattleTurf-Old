#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Ingame.h"
#include "Game_State.h"



/****************************
The intro animation when opening the game
*****************************/
class Intro : public Game_State
{
private:
    sf::RectangleShape introBackground;
    sf::RectangleShape introImageRectangle;
    sf::Texture introImage;
public:
    Intro();
    Intro(sf::RenderWindow *window, Game_data *setting, sf::Font *font);

    void Play();

};

#endif // INTRO_H_INCLUDED
