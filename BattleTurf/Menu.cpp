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
    
    gameTitleRect.setSize(sf::Vector2f(6*ptrsetting->BOX_SIZE, 4*ptrsetting->BOX_SIZE));
    gameTitle.loadFromFile("Texture/image_text_3_2.png");
    gameTitleRect.setTexture(&gameTitle);
    gameTitleRect.setPosition(6*(ptrsetting->BOX_SIZE), 1*(ptrsetting->BOX_SIZE));

    //get the pointers
    ptrwindow = window;
    ptrevent = event;
    ptrMousePosition = mouseposition;
    ptrfont = font;

    //initialize the background
    menu_background.setFillColor(sf::Color(255,255,255,255));
    menu_background.setSize(sf::Vector2f(ptrsetting->NUM_BOX_WIDTH * ptrsetting->BOX_SIZE + ptrsetting->INTERFACE_SIZE,
                                          ptrsetting->NUM_BOX_HEIGHT * ptrsetting->BOX_SIZE));

    //initialize the start button in mainmenu
    startButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 2*ptrsetting->BOX_SIZE,
                                     11*ptrsetting->BOX_SIZE, 8*ptrsetting->BOX_SIZE,
                                     "Texture/button_start_2_1.png", "Texture/button_start_focus_2_1.png");

    //initialize the exit button in mainmenu
    exitButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 2*ptrsetting->BOX_SIZE,
                                    3*ptrsetting->BOX_SIZE, 8*ptrsetting->BOX_SIZE,
                                     "Texture/button_exit_2_1.png", "Texture/button_exit_focus_2_1.png");


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
    ptrwindow->draw(gameTitleRect);

    //in case the menu state is mainmenu
    if(menu_state == mainmenu)
    {
        startButton->addInto(ptrwindow);
        exitButton->addInto(ptrwindow);
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
    if(startButton->isCursor_On_button(ptrMousePosition))
    {
        menu_state = setting1;
    }

     //if the mouse click the "exit" button in mainmenu
    if(exitButton->isCursor_On_button(ptrMousePosition))
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
    
   // if cursor is in menu_start button
    if(startButton->isCursor_On_button(ptrMousePosition))
    {
        //
    }

    //if cursor is in exit button
    if(exitButton->isCursor_On_button(ptrMousePosition))
    {
        //
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
