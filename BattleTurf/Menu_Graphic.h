#ifndef MENU_GRAPHIC_H_INCLUDED
#define MENU_GRAPHIC_H_INCLUDED

#include "Graphic.h"

class Menu_Graphics : public Graphic
{
private:

public:
    //constructor
    Menu_Graphics();

    //show all things in the menu on the window
    void show(sf::RenderWindow &window);

    //hide all things in the menu on the window
    void hide(sf::RenderWindow &window);

};

Menu_Graphics::Menu_Graphics()
{

}

void Menu_Graphics::show(sf::RenderWindow &window)
{

}

void Menu_Graphics::hide(sf::RenderWindow &window)
{

}

#endif // MENU_GRAPHIC_H_INCLUDED
