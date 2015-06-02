#include "Menu.h"
Game_Menu::Game_Menu()
{
    //when the menu start, set the state to mainmenu
    menu_state = mainmenu;
}

Game_Menu::Game_Menu(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *ptrsetting, sf::Font *font)
{
    //when the menu start, set the state to mainmenu
    menu_state = mainmenu;

    //initialize the gametitle picture
    gameTitleRect.setPosition(150,25);
    gameTitleRect.setSize(sf::Vector2f(250,200));
    gameTitle.loadFromFile("Texture/test.png");
    gameTitleRect.setTexture(&gameTitle);

    //get the pointers
    ptrwindow = window;
    ptrevent = event;
    ptrMousePosition = mouseposition;
    ptrfont = font;

    //initialize the background
    menu_background.setFillColor(sf::Color(224,224,224,140));
    menu_background.setSize(sf::Vector2f(ptrsetting->NUM_BOX_WIDTH * ptrsetting->BOX_SIZE + ptrsetting->INTERFACE_SIZE,
                                          ptrsetting->NUM_BOX_HEIGHT * ptrsetting->BOX_SIZE));

    //initialize the start button in mainmenu
    menubutton_start.setFillColor(sf::Color(204,255,153));
    menubutton_start.setPosition(375,250);
    menubutton_start.setSize(sf::Vector2f(150,50));
    menubutton_start_text.setFont(*font);
    menubutton_start_text.setString("Start");
    menubutton_start_text.setColor(sf::Color::Black);
    menubutton_start_text.setCharacterSize(24);
    menubutton_start_text.setPosition(420,260);

    //initialize the exit button in mainmenu
    menubutton_exit.setFillColor(sf::Color(204,255,153));
    menubutton_exit.setPosition(375,425);
    menubutton_exit.setSize(sf::Vector2f(150,50));
    menubutton_exit_text.setFont(*font);
    menubutton_exit_text.setString("Exit");
    menubutton_exit_text.setColor(sf::Color::Black);
    menubutton_exit_text.setCharacterSize(24);
    menubutton_exit_text.setPosition(420,435);

    //the picture of game title
    menu_Title.setFont(*font);
    menu_Title.setString("Battle Turf");
    menu_Title.setCharacterSize(90);
    menu_Title.setPosition(420,50);

    //initialize the next button in setting screen
    settingbutton_next.setFillColor(sf::Color(204,255,153));
    settingbutton_next.setPosition(700,600);
    settingbutton_next.setSize(sf::Vector2f(150,50));
    settingbutton_next_text.setFont(*font);
    settingbutton_next_text.setString("Next");
    settingbutton_next_text.setColor(sf::Color::Black);
    settingbutton_next_text.setCharacterSize(24);
    settingbutton_next_text.setPosition(740,610);

    //initialize the back button in setting screen
    settingbutton_back.setFillColor(sf::Color(204,255,153));
    settingbutton_back.setPosition(200,600);
    settingbutton_back.setSize(sf::Vector2f(150,50));
    settingbutton_back_text.setFont(*font);
    settingbutton_back_text.setString("Back");
    settingbutton_back_text.setColor(sf::Color::Black);
    settingbutton_back_text.setCharacterSize(24);
    settingbutton_back_text.setPosition(240,610);

    //debug: show the current game state
    debug_menustate.setFont(*font);
    debug_menustate.setString("menu_state");
    debug_menustate.setColor(sf::Color::Black);
    debug_menustate.setCharacterSize(14);
    debug_menustate.setPosition(900,610);

}
/*************
update function
ask the window to redraw all graphic element to the screen
*************/
void Game_Menu::update()
{
    //clear the window first
    ptrwindow->clear();
    ptrwindow->draw(menu_background);   //the background must be drawn

    //in case the menu state is mainmenu
    if(menu_state == mainmenu)
    {
        ptrwindow->draw(menu_Title);
        ptrwindow->draw(menubutton_start);
        ptrwindow->draw(menubutton_start_text);
        ptrwindow->draw(menubutton_exit);
        ptrwindow->draw(menubutton_exit_text);
        ptrwindow->draw(gameTitleRect);
    }
    else if(menu_state == setting1)     //setting 1
    {
        ptrwindow->draw(settingbutton_next);
        ptrwindow->draw(settingbutton_next_text);
        ptrwindow->draw(settingbutton_back);
        ptrwindow->draw(settingbutton_back_text);
    }
    else if(menu_state == setting2)     //setting 2
    {
        ptrwindow->draw(settingbutton_next);
        ptrwindow->draw(settingbutton_next_text);
        ptrwindow->draw(settingbutton_back);
        ptrwindow->draw(settingbutton_back_text);
    }
    else if(menu_state == setting3)     //setting 3
    {
        ptrwindow->draw(settingbutton_next);
        ptrwindow->draw(settingbutton_next_text);
        ptrwindow->draw(settingbutton_back);
        ptrwindow->draw(settingbutton_back_text);
    }

    //debug : the game state
    switch(menu_state)
    {
        case mainmenu : debug_menustate.setString("mainmenu"); break;
        case setting1 : debug_menustate.setString("setting1"); break;
        case setting2 : debug_menustate.setString("setting2"); break;
        case setting3 : debug_menustate.setString("setting3"); break;
    }
    ptrwindow->draw(debug_menustate);
    ptrwindow->display();
}

/******************
Mouseclicked
when mouse click something, do something...
******************/
void Game_Menu::Mouseclicked()
{
    //if the mouse click the "start" button in mainmenu
    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 250 && ptrMousePosition->y < 300)
    {
        menu_state = setting1;
    }

     //if the mouse click the "exit" button in mainmenu
    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 425 && ptrMousePosition->y < 475)
    {
        menu_state = terminated;
    }

     //if the mouse click the "next" button in mainmenu
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && ptrMousePosition->x > 700 && ptrMousePosition->x < 850
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        setting_nextButton();
    }

     //if the mouse click the "back" button in mainmenu
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && ptrMousePosition->x > 200 && ptrMousePosition->x < 350
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        setting_backButton();
    }

}
/******************
Mouseclicked
when mouse moved, do something...
******************/
void Game_Menu::Mousemoved()
{
    
    //if cursor is in menu_start button
    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 250 && ptrMousePosition->y < 300)
    {
        menubutton_start.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        menubutton_start.setFillColor(sf::Color(204,255,153));
    }

    //if cursor is in exit button
    if(menu_state == mainmenu && ptrMousePosition->x > 375 && ptrMousePosition->x < 525
       && ptrMousePosition->y > 425 && ptrMousePosition->y < 475)
    {
        menubutton_exit.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        menubutton_exit.setFillColor(sf::Color(204,255,153));
    }

    //if cursor is in next button
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && ptrMousePosition->x > 700 && ptrMousePosition->x < 850
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        settingbutton_next.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        settingbutton_next.setFillColor(sf::Color(204,255,153));
    }

    //if cursor is in back button
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && ptrMousePosition->x > 200 && ptrMousePosition->x < 350
        && ptrMousePosition->y > 600 && ptrMousePosition->y < 650)
    {
        settingbutton_back.setFillColor(sf::Color(128,255,0));
    }
    else
    {
        settingbutton_back.setFillColor(sf::Color(204,255,153));
    }

}
/******************
getMenu_state
return the current menu state
******************/
Menu_state Game_Menu::getMenu_state()
{
    return menu_state;
}
/******************
setting_nextButton
when the "next" button is clicked in setting
screen, change the menu state.
******************/
void Game_Menu::setting_nextButton()
{
    switch(menu_state)
    {
        case setting1 : menu_state = setting2; break;
        case setting2 : menu_state = setting3; break;
        case setting3 : menu_state = end_ingame; break;
    }
}
/******************
setting_backButton
when the "back" button is clicked in setting
screen, change the menu state.
******************/
void Game_Menu::setting_backButton()
{
    switch(menu_state)
    {
        case setting1 : menu_state = mainmenu; break;
        case setting2 : menu_state = setting1; break;
        case setting3 : menu_state = setting2; break;
    }
}
