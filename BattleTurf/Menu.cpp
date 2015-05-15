#include "Menu.h"
Game_Menu::Game_Menu()
{
    menu_state = mainmenu;
}

Game_Menu::Game_Menu(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *ptrsetting, sf::Font *font)
{
    menu_state = mainmenu;
    ptrwindow = window;
    ptrevent = event;
    ptrMousePosition = mouseposition;
    ptrfont = font;

    menu_background.setFillColor(sf::Color(224,224,224,140));
    menu_background.setSize(sf::Vector2f(ptrsetting->NUM_BOX_WIDTH * ptrsetting->BOX_SIZE + ptrsetting->INTERFACE_SIZE,
                                          ptrsetting->NUM_BOX_HEIGHT * ptrsetting->BOX_SIZE));

    menubutton_start.setFillColor(sf::Color(204,255,153));
    menubutton_start.setPosition(375,225);
    menubutton_start.setSize(sf::Vector2f(150,50));
    menubutton_start_text.setFont(*font);
    menubutton_start_text.setString("Start");
    menubutton_start_text.setColor(sf::Color::Black);
    menubutton_start_text.setCharacterSize(24);
    menubutton_start_text.setPosition(420,235);

    menubutton_exit.setFillColor(sf::Color(204,255,153));
    menubutton_exit.setPosition(375,425);
    menubutton_exit.setSize(sf::Vector2f(150,50));
    menubutton_exit_text.setFont(*font);
    menubutton_exit_text.setString("Exit");
    menubutton_exit_text.setColor(sf::Color::Black);
    menubutton_exit_text.setCharacterSize(24);
    menubutton_exit_text.setPosition(420,435);

    menu_Title.setFont(*font);
    menu_Title.setString("Battle Turf");
    menu_Title.setCharacterSize(90);
    menu_Title.setPosition(250,50);

    settingbutton_next.setFillColor(sf::Color(204,255,153));
    settingbutton_next.setPosition(700,600);
    settingbutton_next.setSize(sf::Vector2f(150,50));
    settingbutton_next_text.setFont(*font);
    settingbutton_next_text.setString("Next");
    settingbutton_next_text.setColor(sf::Color::Black);
    settingbutton_next_text.setCharacterSize(24);
    settingbutton_next_text.setPosition(740,610);

    settingbutton_back.setFillColor(sf::Color(204,255,153));
    settingbutton_back.setPosition(200,600);
    settingbutton_back.setSize(sf::Vector2f(150,50));
    settingbutton_back_text.setFont(*font);
    settingbutton_back_text.setString("Back");
    settingbutton_back_text.setColor(sf::Color::Black);
    settingbutton_back_text.setCharacterSize(24);
    settingbutton_back_text.setPosition(240,610);

}

void Game_Menu::update()
{
    ptrwindow->clear();
    ptrwindow->draw(menu_background);   //the background must be drawn
    if(menu_state == mainmenu)
    {
        ptrwindow->draw(menu_Title);
        ptrwindow->draw(menubutton_start);
        ptrwindow->draw(menubutton_start_text);
        ptrwindow->draw(menubutton_exit);
        ptrwindow->draw(menubutton_exit_text);
    }
    else if(menu_state == setting1)
    {
        ptrwindow->draw(settingbutton_next);
        ptrwindow->draw(settingbutton_next_text);
        ptrwindow->draw(settingbutton_back);
        ptrwindow->draw(settingbutton_back_text);
    }

    ptrwindow->display();
}


void Game_Menu::Mouseclicked()
{
    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 225 && ptrMousePosition->y < 275)
    {
        menu_state = setting1;
    }

    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 425 && ptrMousePosition->y < 475)
    {
        menu_state = terminated;
    }

    if(menu_state == setting1 && ptrMousePosition->x > 700 && ptrMousePosition->x < 850
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        menu_state = end_ingame;
    }

    if(menu_state == setting1 && ptrMousePosition->x > 200 && ptrMousePosition->x < 350
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        menu_state = mainmenu;
    }
}

void Game_Menu::Mousemoved()
{
    //if cursor is in menu_start button
    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 225 && ptrMousePosition->y < 275)
    {
        menubutton_start.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        menubutton_start.setFillColor(sf::Color(204,255,153));
    }

    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 425 && ptrMousePosition->y < 475)
    {
        menubutton_exit.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        menubutton_exit.setFillColor(sf::Color(204,255,153));
    }
    if(menu_state == setting1 && ptrMousePosition->x > 700 && ptrMousePosition->x < 850
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        settingbutton_next.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        settingbutton_next.setFillColor(sf::Color(204,255,153));
    }

    if(menu_state == setting1 && ptrMousePosition->x > 200 && ptrMousePosition->x < 350
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        settingbutton_back.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        settingbutton_back.setFillColor(sf::Color(204,255,153));
    }

}

Menu_state Game_Menu::getMenu_state()
{
    return menu_state;
}
