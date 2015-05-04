#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>

class Game_Menu
{
private:
    //the button(?) of menu
    sf::RectangleShape menubutton;
    sf::RenderWindow *ptrwindow;
    sf::Event *ptrevent;
public:
    //constructor
    Game_Menu();
    //Initialize the elements
    void Initialize(sf::RenderWindow *window, sf::Event *event);

    //update the graphic
    void update();
};

#endif // MENU_H_INCLUDED
