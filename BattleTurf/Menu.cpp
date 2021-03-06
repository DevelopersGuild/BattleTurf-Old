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

    //initialize the multiplayer button in mainmenu
    multiPlayerButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 2*ptrsetting->BOX_SIZE,
                                     11*ptrsetting->BOX_SIZE, 5*ptrsetting->BOX_SIZE,
                                     "Texture/button_start_2_1.png", "Texture/button_start_focus_2_1.png");

    //initialize the exit button in mainmenu
    exitButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 2*ptrsetting->BOX_SIZE,
                                    3*ptrsetting->BOX_SIZE, 8*ptrsetting->BOX_SIZE,
                                     "Texture/button_exit_2_1.png", "Texture/button_exit_focus_2_1.png");

    nextButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 1*ptrsetting->BOX_SIZE,
                                    11*ptrsetting->BOX_SIZE, 10*ptrsetting->BOX_SIZE,
                                    "Texture/button_next_4_1.png", "Texture/button_next_focus_4_1.png");

    backButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 1*ptrsetting->BOX_SIZE,
                                    3*ptrsetting->BOX_SIZE, 10*ptrsetting->BOX_SIZE,
                                    "Texture/button_back_4_1.png", "Texture/button_back_focus_4_1.png");

    hostButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 1*ptrsetting->BOX_SIZE,
                                    7*ptrsetting->BOX_SIZE, 8*ptrsetting->BOX_SIZE,
                                    "Texture/button_back_4_1.png", "Texture/button_back_focus_4_1.png");

    clientButton = new Graphic_button(4*ptrsetting->BOX_SIZE, 1*ptrsetting->BOX_SIZE,
                                    7*ptrsetting->BOX_SIZE, 10*ptrsetting->BOX_SIZE,
                                    "Texture/button_back_4_1.png", "Texture/button_back_focus_4_1.png");

    //debug: show the current game state
    debug_menustate.setFont(*font);
    debug_menustate.setString("menu_state");
    debug_menustate.setColor(sf::Color::Black);
    debug_menustate.setCharacterSize(14);
    debug_menustate.setPosition(900,610);

}
/*************
Destructor
remove all elements in the menu
*************/
Game_Menu::~Game_Menu()
{
    delete startButton;
    delete multiPlayerButton;
    delete exitButton;
    delete nextButton;
    delete backButton;
    delete hostButton;
    delete clientButton;
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
        multiPlayerButton->addInto(ptrwindow);
        exitButton->addInto(ptrwindow);
    }
    else if(menu_state == setting1)     //setting 1
    {
        nextButton->addInto(ptrwindow);
        backButton->addInto(ptrwindow);
    }
    else if(menu_state == setting2)     //setting 2
    {
        nextButton->addInto(ptrwindow);
        backButton->addInto(ptrwindow);
    }
    else if(menu_state == setting3)     //setting 3
    {
        nextButton->addInto(ptrwindow);
        backButton->addInto(ptrwindow);
    }
    else if(menu_state == multiplayer1)
    {
        hostButton->addInto(ptrwindow);
        clientButton->addInto(ptrwindow);
    }

    //debug : the game state
    switch(menu_state)
    {
        case mainmenu : debug_menustate.setString("mainmenu"); break;
        case setting1 : debug_menustate.setString("setting1"); break;
        case setting2 : debug_menustate.setString("setting2"); break;
        case setting3 : debug_menustate.setString("setting3"); break;
        case multiplayer1 : debug_menustate.setString("multiplayer1"); break;
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
    if(menu_state == mainmenu && startButton->isCursor_On_button(ptrMousePosition))
    {
        menu_state = setting1;
    }

     //if the mouse click the "exit" button in mainmenu
    if(menu_state == mainmenu && exitButton->isCursor_On_button(ptrMousePosition))
    {
        menu_state = terminated;
    }

    //if the mouse click "multiplayer" button in mainmenu
    if(menu_state == mainmenu && multiPlayerButton->isCursor_On_button(ptrMousePosition))
    {
        menu_state = multiplayer1;
    }

     //if the mouse click the "next" button in mainmenu
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && nextButton->isCursor_On_button(ptrMousePosition))
    {
        setting_nextButton();
    }

     //if the mouse click the "back" button in mainmenu
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && backButton->isCursor_On_button(ptrMousePosition))
    {
        setting_backButton();
    }

    //if the mouse click "host" button in multiplayer1
    if(menu_state == multiplayer1 && hostButton->isCursor_On_button(ptrMousePosition))
    {

    }

    //if the mouse click "client" button in multiplayer1
    if(menu_state == multiplayer1 && clientButton->isCursor_On_button(ptrMousePosition))
    {
        //
    }

}
/******************
MouseMoved
when mouse moved, do something...
******************/
void Game_Menu::Mousemoved()
{
   // if cursor is in menu_start button
    if(menu_state == mainmenu && startButton->isCursor_On_button(ptrMousePosition))
    {
        //
    }

    //if cursor is in exit button
    if(menu_state == mainmenu && exitButton->isCursor_On_button(ptrMousePosition))
    {
        //
    }

    //if cursor in in multiplayer
    if(menu_state == mainmenu && multiPlayerButton->isCursor_On_button(ptrMousePosition))
    {
        //
    }

    //if cursor is in next button
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && nextButton->isCursor_On_button(ptrMousePosition))
    {

    }

    //if cursor is in back button
    if((menu_state == setting1 || menu_state == setting2 || menu_state == setting3)
        && backButton->isCursor_On_button(ptrMousePosition))
    {

    }

    //if cursor is in host button
    if(menu_state == multiplayer1 && hostButton->isCursor_On_button(ptrMousePosition))
    {
        std::cout << "Debug: Host button" << std::endl;
    }

    //if cursor is in client button
    if(menu_state == multiplayer1 && clientButton->isCursor_On_button(ptrMousePosition))
    {
        std::cout << "Debug : Client button" << std::endl;
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
