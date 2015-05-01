#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED
#include <SFML/Graphics.hpp>

class Graphic
{
public:
    //show that graphics on the window
    virtual void show(sf::RenderWindow &) = 0;

    //hide that graphics on the window
    virtual void hide(sf::RenderWindow &) = 0;

    //clear the window, only the game can access it, but currently I leave it here...
    //virtual void clear()

};

#endif // GRAPHIC_H_INCLUDED
