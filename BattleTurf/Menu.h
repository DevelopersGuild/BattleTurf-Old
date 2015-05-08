#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Ingame.h"

enum Menu_state{mainmenu = 1, setting1 = 2, setting2 = 3, setting3 = 4, end_ingame = 5};

class Game_Menu
{
private:
    //the font used
    sf::Font *ptrfont;
    sf::Text menu_Title;
    sf::Vector2i *ptrmouseposition;

    //the background of menu
    sf::RectangleShape menu_background;
    //the button(s) of menu
    sf::RectangleShape menubutton_start;
    sf::Text menubutton_start_text;

    sf::RectangleShape menubutton_exit;
    sf::Text menubutton_exit_text;

    Game_data *ptrsetting;
    Menu_state menu_state;

    sf::RenderWindow *ptrwindow;
    const sf::Event *ptrevent;
public:
    //constructor
    Game_Menu();
    //Initialize the elements
    void Initialize(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *ptrsetting, sf::Font *font);

    //update the graphic
    void update();

    Menu_state getMenu_state();

    //Handle the events
    void Mouseclicked();

    void Mousemoved();
};

#endif // MENU_H_INCLUDED
