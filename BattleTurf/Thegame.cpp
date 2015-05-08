#include "Thegame.h"
/*****************************************************
Constructor
*****************************************************/
Game::Game()
{
    game_state = Start;

    //temporary set the game data, will be changed later
    game.NUM_WALL = 8;         //number of wall
    game.NUM_PLAYER = 4;       //number of player, must be less or equals to than 4
    game.NUM_BOX_WIDTH = 11;    //the width of the map
    game.NUM_BOX_HEIGHT = 11;   //the height of the map
    game.NUM_SCORE_EACH_PLAYER = ((game.NUM_BOX_WIDTH * game.NUM_BOX_HEIGHT) - game.NUM_WALL) / game.NUM_PLAYER;       //the number of score box that each player can put in the game
    game.BOX_SIZE = 55;        //the size of the box
    game.INTERFACE_SIZE = game.NUM_BOX_WIDTH * game.BOX_SIZE / 2; //the width of the interface

    font = new sf::Font;
    font->loadFromFile("arial.ttf");

    intro.Init(&window, &game, font);
    ingame.Init(&window,&event,&mouseposition, &game, font);
    menu.Initialize(&window,&event,&mouseposition, &game, font);

}
/*********************************************
start()
Create window, update Graphics and loop the events.
*********************************************/
void Game::start()
{

    window.create(sf::VideoMode(game.NUM_BOX_WIDTH * game.BOX_SIZE + game.INTERFACE_SIZE, game.NUM_BOX_HEIGHT * game.BOX_SIZE),
                   "BattleTurf",sf::Style::Close);
    //start with intro
    //menu.update();
    while(window.isOpen())
    {
        //update the position of mouse
        getMousePosition();
        if(game_state == Start)
        {
            intro.Play();
            game_state = Menu;
        }
        else if(game_state == Menu)
        {
            menu.update();
            if(window.waitEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::MouseButtonPressed)
                {
                    game_state = Maingame;
                }

                if(event.type == sf::Event::MouseMoved)
                {
                    menu.Mousemoved();
                }
            }
        }
        else if(game_state == Maingame)
        {
            ingame.update();
            ingame.Show_Cursor_Box();
            if(window.waitEvent(event))
                ingame.HandleEvent();
        }
    }
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
    if(isMouseinGame())
    mouseposition = sf::Mouse::getPosition(window);
}

/*********************************************
isMousfeinGame
is Mouse in the map?
*********************************************/
bool Game::isMouseinGame()
{
    if( sf::Mouse::getPosition(window).x > 0
        && sf::Mouse::getPosition(window).y > 0
        && sf::Mouse::getPosition(window).x < game.NUM_BOX_WIDTH * game.BOX_SIZE
        && sf::Mouse::getPosition(window).y < game.NUM_BOX_HEIGHT * game.BOX_SIZE)
    {
         return true;
    }
    return false;
}
