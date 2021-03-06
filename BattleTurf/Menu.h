#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Ingame.h"
#include "Game_State.h"
#include "Graphic_button.h"

enum Menu_state{mainmenu = 1,
                setting1 = 2, setting2 = 3, setting3 = 4,
                multiplayer1 = 5, multiplayer2 = 6,
                end_ingame = 10, end_multiplayer_ingame = 11,
                terminated = 12};

class Game_Menu : public Game_State
{
private:

    //the background of menu
    sf::RectangleShape menu_background;

    Graphic_button* startButton;
    Graphic_button* multiPlayerButton;
    Graphic_button* exitButton;

    Graphic_button* nextButton;
    Graphic_button* backButton;

    Graphic_button* hostButton;
    Graphic_button* clientButton;

    //the (testing) image of menu
    sf::Texture gameTitle;
    sf::RectangleShape gameTitleRect;

    //sf::RectangleShape menubutton_exit;
    //sf::Text menubutton_exit_text;
    Graphic_button* menubutton_exit;

    //debug text
    sf::Text debug_menustate;

    Menu_state menu_state;

    void setting_nextButton();
    void setting_backButton();


public:
    //constructor
    Game_Menu();
    Game_Menu(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *ptrsetting, sf::Font *font);

    //destructor
    ~Game_Menu();

    //update the graphic
    void update();

    Menu_state getMenu_state();

    //Handle the events
    void Mouseclicked();

    void Mousemoved();
};

#endif // MENU_H_INCLUDED
