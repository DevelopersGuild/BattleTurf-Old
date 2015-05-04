#include "Menu.h"
Game_Menu::Game_Menu()
{
}

void Game_Menu::Initialize(sf::RenderWindow *window, sf::Event *event)
{
    menubutton.setFillColor(sf::Color::Blue);
    menubutton.setPosition(50,50);
    menubutton.setSize(sf::Vector2f(150,50));

    ptrwindow = window;
    ptrevent = event;
}

void Game_Menu::update()
{
    ptrwindow->clear();
    ptrwindow->draw(menubutton);
    ptrwindow->display();
}
