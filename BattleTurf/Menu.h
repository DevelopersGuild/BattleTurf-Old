#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Ingame.h"
#include "Game_State.h"
#include "Graphic_button.h"

enum Menu_state{mainmenu = 1, setting1 = 2, setting2 = 3, setting3 = 4, end_ingame = 5, terminated = 6};

class Game_Menu : public Game_State
{
private:

    //the background of menu
    sf::RectangleShape menu_background;

    Graphic_button* startButton;
    Graphic_button* exitButton;
    Graphic_button* nextButton;
    Graphic_button* backButton;


    //the (testing) image of menu
    sf::Texture gameTitle;
    sf::RectangleShape gameTitleRect;


    sf::RectangleShape settingbutton_next;
    sf::Text settingbutton_next_text;

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
