#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Ingame.h"
#include "Game_State.h"

enum Menu_state{mainmenu = 1, setting1 = 2, setting2 = 3, setting3 = 4, end_ingame = 5, terminated = 6};

class Game_Menu : public Game_State
{
private:
    sf::Text menu_Title;

    //the background of menu
    sf::RectangleShape menu_background;

    //the (testing) image of menu
    sf::Texture gameTitle;
    sf::RectangleShape gameTitleRect;
    //the button(s) of menu
    sf::RectangleShape menubutton_start;
    sf::Text menubutton_start_text;
    sf::RectangleShape menubutton_exit;
    sf::Text menubutton_exit_text;

    sf::RectangleShape settingbutton_next;
    sf::Text settingbutton_next_text;

    sf::RectangleShape settingbutton_back;
    sf::Text settingbutton_back_text;

    //debug text
    sf::Text debug_menustate;

    Menu_state menu_state;

    void setting_nextButton();
    void setting_backButton();

public:
    //constructor
    Game_Menu();
    Game_Menu(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *ptrsetting, sf::Font *font);

    //update the graphic
    void update();

    Menu_state getMenu_state();

    //Handle the events
    void Mouseclicked();

    void Mousemoved();
};

#endif // MENU_H_INCLUDED
