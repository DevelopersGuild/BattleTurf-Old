#include "Thegame.h"
/*****************************************************
Constructor
*****************************************************/
Game::Game()
{
    game_state = Start;
    videoMode = sf::VideoMode::getFullscreenModes()[0];

    //temporary set the game data, will be changed later
    gamedata.NUM_WALL = 8;         //number of wall
    gamedata.NUM_PLAYER = 4;       //number of player, must be less or equals to than 4
    gamedata.NUM_BOX_WIDTH = 12;    //the width of the map
    gamedata.NUM_BOX_HEIGHT = 12;   //the height of the map
    gamedata.NUM_SCORE_EACH_PLAYER = ((gamedata.NUM_BOX_WIDTH * gamedata.NUM_BOX_HEIGHT) - gamedata.NUM_WALL - (gamedata.NUM_BOX_HEIGHT - 1) * 4) / gamedata.NUM_PLAYER;       //the number of score box that each player can put in the gamedata
    gamedata.BOX_SIZE = static_cast<int> (videoMode.height/15);        //the size of the box
    gamedata.INTERFACE_SIZE = gamedata.NUM_BOX_WIDTH * gamedata.BOX_SIZE / 2; //the width of the interface

    font = new sf::Font;
    font->loadFromFile("arial.ttf");
    ingame = NULL;

}
/*********************************************
start()
Create window, update Graphics and loop the events.
*********************************************/
void Game::start()
{
    window.create(sf::VideoMode(gamedata.NUM_BOX_WIDTH * gamedata.BOX_SIZE + gamedata.INTERFACE_SIZE, gamedata.NUM_BOX_HEIGHT * gamedata.BOX_SIZE),
                  "BattleTurf",sf::Style::Close);
    //start with intro
    //menu.update();
    while(window.isOpen())
    {
        //update the position of mouse
        getMousePosition();
        if(game_state == Start)
        {
            intro = new Intro(&window, &gamedata, font);
            intro->Play();
            delete intro;
            game_state = Menu;
            menu = new Game_Menu(&window,&event,&mouseposition, &gamedata, font);
        }
        else if(game_state == Menu)
        {
            menu->update();

            if(menu->getMenu_state() == end_ingame)
            {
                game_state = Maingame;
                delete menu;
                ingame = new Ingame(&window,&event,&mouseposition, &gamedata, font);
            }
            else if(menu->getMenu_state() == terminated)
            {
                delete menu;
                window.close();
            }

            if(window.waitEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::MouseButtonPressed)
                {
                    if(isMouseinWindow())
                    menu->Mouseclicked();
                }

                if(event.type == sf::Event::MouseMoved)
                {
                    menu->Mousemoved();
                }
            }
        }
        else if(game_state == Maingame)
        {
            ingame->update();

            if(window.waitEvent(event))
                ingame->HandleEvent();
        }
    }
    if(ingame)
    delete ingame;
}

/*********************************************
getMousePosition
When mouse moved,
change the value that record the position of the mouse,
and determine the box that the cursor is pointing at.
*********************************************/
void Game::getMousePosition()
{
    //get the position of the mouse, make sure the mouse is in the window!
    if(game_state == Maingame) // if the game started, make sure it is in the map
    {
            mouseposition = sf::Mouse::getPosition(window);
    }
    else if(isMouseinWindow())
    {
        mouseposition = sf::Mouse::getPosition(window);
    }

}

/*********************************************
isMousfeingamedata
is Mouse in the map?
*********************************************/
bool Game::isMouseingame()
{
    if( sf::Mouse::getPosition(window).x > 0
        && sf::Mouse::getPosition(window).y > 0
        && sf::Mouse::getPosition(window).x < gamedata.NUM_BOX_WIDTH * gamedata.BOX_SIZE
        && sf::Mouse::getPosition(window).y < gamedata.NUM_BOX_HEIGHT * gamedata.BOX_SIZE)
    {
        std::cout << "true" << std::endl;
         return true;
    }
    std::cout << "false" << std::endl;
    return false;
}

bool Game::isMouseinWindow()
{
        if( sf::Mouse::getPosition(window).x > 0
        && sf::Mouse::getPosition(window).y > 0
        && sf::Mouse::getPosition(window).x < window.getSize().x
        && sf::Mouse::getPosition(window).y < window.getSize().y)
        {
            return true;
        }
        return false;
}
