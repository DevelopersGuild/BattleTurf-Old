#include "Thegame.h"
/*****************************************************
Constructor
*****************************************************/
Game::Game()
{
    /*****************************
    Game operating
    *****************************/
    srand(time(NULL));
    current_active_player = 0;
    turn_passed = 0;
    for(int i = 0; i < NUM_PLAYER; i++)
    {
        player[i].Initialize(NUM_SCORE_EACH_PLAYER);
    }
    lastbox = NULL;
    Mech_Set_Score_Pool();
    Mech_Set_Wall();
    /*****************************
    Graphics
    *****************************/
    //this is temporary, will be changed after we create the menu
    sf::Color playercolors[4];
    playercolors[0] = sf::Color::Blue;
    playercolors[1] = sf::Color::Red;
    playercolors[2] = sf::Color::Green;
    playercolors[3] = sf::Color::Yellow;
    for(int i = 0; i < NUM_PLAYER; i++)
    {
        player[i].setcolor(playercolors[i]);
    }

    for(int i = 0; i < NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < NUM_BOX_HEIGHT; j++)
        {
            box[i][j].setrect(BOX_SIZE, BOX_SIZE * i, BOX_SIZE * j,2);
        }
    }

    font.loadFromFile("arial.ttf");

    for(int i = 0; i < NUM_BOX_WIDTH; i++)          //initializing each element of score[][]
    {
        for(int j = 0; j < NUM_BOX_HEIGHT; j++)
        {
            Graphing_score[i][j].setFont(font);
            Graphing_score[i][j].setColor(sf::Color::Black);
            Graphing_score[i][j].setCharacterSize(30);
            Graphing_score[i][j].setStyle(sf::Text::Regular);
            Graphing_score[i][j].setString("0");
            Graphing_score[i][j].setPosition(BOX_SIZE * i, BOX_SIZE * j);
        }
    }

    GraphingRect1.setFillColor(sf::Color::Blue);         //becuase the color of the first player is blue
    GraphingRect1.setSize(sf::Vector2f(INTERFACE_SIZE, NUM_BOX_HEIGHT * BOX_SIZE / 2));      //the size
    GraphingRect1.setPosition(sf::Vector2f(NUM_BOX_WIDTH * BOX_SIZE + 5, 0));                //the position
    GraphingRect1.setOutlineThickness(5);                //Outline, the "border" of the rectangle
    GraphingRect1.setOutlineColor(sf::Color::Black);     //the color of the outline is black

    Graphing_scorebox.setFont(font);
    Graphing_scorebox.setColor(sf::Color::Black);
    Graphing_scorebox.setCharacterSize(60);
    Graphing_scorebox.setStyle(sf::Text::Regular);
    Graphing_scorebox.setPosition(NUM_BOX_WIDTH * BOX_SIZE + (INTERFACE_SIZE / 2), INTERFACE_SIZE / 3);

    for(int i = 0; i < NUM_PLAYER; i++)
    {
        Graphing_player_score[i].setFont(font);
        Graphing_player_score[i].setColor(sf::Color::White);
        Graphing_player_score[i].setCharacterSize(30);
        Graphing_player_score[i].setStyle(sf::Text::Regular);
        Graphing_player_score[i].setString("0");
        Graphing_player_score[i].setPosition(NUM_BOX_WIDTH * BOX_SIZE, INTERFACE_SIZE + i * 20);
    }
}
/*********************************************
start()
Create window, update Graphics and loop the events.
*********************************************/
void Game::start()
{
    window.create(sf::VideoMode(NUM_BOX_WIDTH * BOX_SIZE + INTERFACE_SIZE, NUM_BOX_HEIGHT * BOX_SIZE), "BattleTurf",sf::Style::Close);
    while(window.isOpen())
    {
        sf::Event event;

        Graphic_updateAll();        //update graphics when event occurred

        if(window.waitEvent(event))
        {
            HandleEvent(event);
        }
    }
    //Show the winner, will be changed when we do the graphics
    std::cout << "The winner is Player" << Mech_Find_winner() + 1 << " ! ";
}
/*********************************************
Graphic_updateAll
Refresh all the graphics
*********************************************/
void Game::Graphic_updateAll()
{
    window.clear();
    //redraw the map, will be changed when we do the graphics.
    for(int i = 0; i < NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < NUM_BOX_HEIGHT;j++)
        {
            box[i][j].show(&window);

            if(box[i][j].getscore() != 0)
                window.draw(Graphing_score[i][j]);
        }
    }
    //draw the background behind the text that shows the current player's color and his scorebox
    window.draw(GraphingRect1);
    //change the background color of the background
    GraphingRect1.setFillColor(player[current_active_player].getcolor());
    //show the current scorebox
    Graphic_int_ToString(player[current_active_player].getscore_order(turn_passed), Graphing_scorebox);
    //draw the scorebox
    window.draw(Graphing_scorebox);
    //the total score of each player
    for(int i = 0; i < NUM_PLAYER; i++)
    {
        Graphic_int_ToString(player[i].getscore(),Graphing_player_score[i]);
        window.draw(Graphing_player_score[i]);
    }

    window.display();
}
/*********************************************
HandleEvent
Call the function according to the event occurred
*********************************************/
void Game::HandleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
    window.close();

    if (event.type == sf::Event::MouseMoved)
    {
        Event_MouseMoved();
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Event_MouseLeftClicked();
    }
}
/*********************************************
Event_MouseMoved
When mouse moved,
change the value that record the position of the mouse,
and determine the box that the cursor is pointing at.
*********************************************/
void Game::Event_MouseMoved()
{
    //get the position of the mouse, make sure the mouse is in the window!
    if(isMouseinGame())
    mouseposition = sf::Mouse::getPosition(window);
    //get the current box
    currentbox = &box[mouseposition.x / BOX_SIZE][mouseposition.y / BOX_SIZE];
    if(currentbox != lastbox)
    {
        Graphic_Show_Cursor_CurrentBox(currentbox,lastbox);
        lastbox = currentbox;
    }
}
/*********************************************
Event_MouseLeftClicked
When player click the left button,
try to capture the box, if success, update the map.
Then check the adjacent tile.
Then change to the next player.
And Finally calculate the total score.
*********************************************/
void Game::Event_MouseLeftClicked()
{
    if(currentbox->capture_directly_by(player[current_active_player], player[current_active_player].getscore_order(turn_passed)))
    {
        //update the graphing score
        Graphic_int_ToString(player[current_active_player].getscore_order(turn_passed),
                             Graphing_score[mouseposition.x / BOX_SIZE][mouseposition.y / BOX_SIZE]);
        //attack or strengthen the nearby boxes
        Mech_Check_adjacent(mouseposition, currentbox, box, Graphing_score);

        Mech_NextPlayer();
        //count the score, the algorithm is not good and will be changed later
        Mech_Reset_Player_Scores();

        Mech_Calculate_Score();
    }
}
/*********************************************
Graphic_int_ToString
convert the integer to sf::Text
This is important when trying to show the score via sf::Text graphic elements.
*********************************************/
void Game::Graphic_int_ToString(int value, sf::Text &targettext)
{
    char buf[256];
    sprintf(buf, "%d", value);
    targettext.setString(buf);
}
/*********************************************
Graphic_Show_Cursor_CurrentBox
Lighten the cursor's location to cyan color and set the last box to normal
*********************************************/
void Game::Graphic_Show_Cursor_CurrentBox(Box *currentbox, Box *lastbox)
{
    //the current box turns cyan
    if(currentbox->getstate() == 0)
    {
        currentbox->setFillColor(sf::Color::Cyan);
    }
    //the lastbox changes to white, if the lastbox is occupied, don't chnange it to white.
    if(lastbox !=NULL && lastbox->getstate() == 0)
    {
        lastbox->setFillColor(sf::Color::White);
    }
}
/*********************************************
Mech_Check_adjacent
"Try" to capture the surrounding tiles.
*********************************************/
void Game::Mech_Check_adjacent(sf::Vector2i mouseposition,Box *currentbox, Box box[][NUM_BOX_HEIGHT],sf::Text score[][NUM_BOX_HEIGHT])
{
        //up
    if( currentbox != &box[mouseposition.x / BOX_SIZE][0] && (currentbox - 1)->check(currentbox))
    {
        //if success, update the graphing score
        Graphic_int_ToString((currentbox - 1)->getscore(),
                             score[mouseposition.x / BOX_SIZE][(mouseposition.y / BOX_SIZE) - 1]);
    }
    //bottom
    if( currentbox != &box[mouseposition.x / BOX_SIZE][NUM_BOX_HEIGHT - 1] && (currentbox + 1)->check(currentbox))
    {
        Graphic_int_ToString((currentbox + 1)->getscore(),
                             score[mouseposition.x / BOX_SIZE][(mouseposition.y / BOX_SIZE) + 1]);
    }
    //left
    if( currentbox != &box[0][mouseposition.y / BOX_SIZE] && (currentbox - NUM_BOX_HEIGHT)->check(currentbox))
    {
        Graphic_int_ToString((currentbox - NUM_BOX_HEIGHT)->getscore(),
                             score[(mouseposition.x / BOX_SIZE) - 1][mouseposition.y / BOX_SIZE]);
    }
    //right
    if( currentbox != &box[NUM_BOX_WIDTH - 1][mouseposition.y / BOX_SIZE] && (currentbox + NUM_BOX_HEIGHT)->check(currentbox))
    {
        Graphic_int_ToString((currentbox + NUM_BOX_HEIGHT)->getscore(),
                             score[(mouseposition.x / BOX_SIZE) + 1][mouseposition.y / BOX_SIZE]);
    }
    //left top
    if( currentbox != &box[mouseposition.x / BOX_SIZE][0]
        && currentbox != &box[0][mouseposition.y / BOX_SIZE]
        && (currentbox - NUM_BOX_HEIGHT - 1)->check(currentbox))
    {
        Graphic_int_ToString((currentbox - NUM_BOX_HEIGHT - 1)->getscore(),
                             score[(mouseposition.x / BOX_SIZE) - 1][(mouseposition.y / BOX_SIZE) - 1]);
    }
    //left bottom
    if( currentbox != &box[0][mouseposition.y / BOX_SIZE]
        && currentbox != &box[mouseposition.x / BOX_SIZE][NUM_BOX_HEIGHT - 1]
        && (currentbox - NUM_BOX_HEIGHT + 1)->check(currentbox))
    {
        Graphic_int_ToString((currentbox - NUM_BOX_HEIGHT + 1)->getscore(),
                             score[(mouseposition.x / BOX_SIZE) - 1][(mouseposition.y / BOX_SIZE) + 1]);
    }
    //right top
    if( currentbox != &box[NUM_BOX_WIDTH - 1][mouseposition.y / BOX_SIZE]
        && currentbox != &box[mouseposition.x / BOX_SIZE][0]
        && (currentbox + NUM_BOX_HEIGHT - 1)->check(currentbox))
    {
        Graphic_int_ToString((currentbox + NUM_BOX_HEIGHT - 1)->getscore(),
                             score[(mouseposition.x / BOX_SIZE) + 1][(mouseposition.y / BOX_SIZE) - 1]);
    }
    //right bottom
    if( currentbox != &box[NUM_BOX_WIDTH - 1][mouseposition.y / BOX_SIZE]
        && currentbox != &box[mouseposition.x / BOX_SIZE][NUM_BOX_HEIGHT - 1]
        && (currentbox + NUM_BOX_HEIGHT + 1)->check(currentbox))
    {
        Graphic_int_ToString((currentbox + NUM_BOX_HEIGHT + 1)->getscore(),
                             score[(mouseposition.x / BOX_SIZE) + 1][(mouseposition.y / BOX_SIZE) + 1]);
    }
}
/*********************************************
Mech_Reset_Player_Scores
Set all player's score to 0.
*********************************************/
void Game::Mech_Reset_Player_Scores()
{
    for(int i = 0; i < NUM_PLAYER; i++)
    {
        player[i].resetscore();
    }
}
/*********************************************
Mech_Calculate_Score
GO over the map and calculate the score of each player
*********************************************/
void Game::Mech_Calculate_Score()
{
    for(int i = 0; i < NUM_BOX_WIDTH; i++)      //go over every box and count the score
    {
        for(int j = 0; j < NUM_BOX_HEIGHT; j++)
        {

            if( box[i][j].getstate() == 1)        //if somebody occupied the box
            {
                (box[i][j].getowner())->addscore(box[i][j].getscore());
            }
        }
    }
}
/*********************************************
Mech_Set_Score_Pool
Randomize the scorebox_order for each player
*********************************************/
void Game::Mech_Set_Score_Pool()
{
    int score_pool[NUM_SCORE_EACH_PLAYER];
    //assign to each player with randomized order
    for(int i = 0; i < NUM_PLAYER; i++)
    {
        for(int j = 0; j < NUM_SCORE_EACH_PLAYER; j++)
        {
            score_pool[j] = rand() % 25 + 5;
        }
        player[i].setscorebox_order(score_pool,NUM_SCORE_EACH_PLAYER);
    }
}
/*********************************************
Mech_Set_Wall
Randomly pick some tiles and turn them to walls
*********************************************/
void Game::Mech_Set_Wall()
{
    int count = 0;
    while(count < NUM_WALL)
    {
        int target1 = rand() % NUM_BOX_WIDTH;
        int target2 = rand() % NUM_BOX_HEIGHT;
        if(box[target1][target2].getstate() != 2)
        {
            box[target1][target2].setwall();
            count++;
        }
    }
}
/*********************************************
Mech_Rearrange_order
change the player order, from lowest score to highest score
*********************************************/
void Game::Mech_Rearrange_order()
{

}
/*********************************************
Mech_NextPlayer
go to next player, if all player have finished that turn,
reset current_active_player back to 0(player1), and add 1 to turn_passed
*********************************************/
void Game::Mech_NextPlayer()
{
    //next player move
    current_active_player++;
    //if it is the last player of that turn, reset to player1.
    if(current_active_player == NUM_PLAYER)
    {
        //Mech_Rearrange_order();
        current_active_player = 0;
        turn_passed++;               //next turn.
    }
}
/*********************************************
Mech_Find_winner
Find winner. Noted that this function doesn't work if players
have the same score.
*********************************************/
int Game::Mech_Find_winner()
{
    int winner = 0;
    for(int i = 1; i < NUM_PLAYER; i++)
    {
        if(player[winner].getscore() < player[i].getscore())
            winner = i;
    }
    return winner;
}
/*********************************************
isMousfeinGame
is Mouse in the map?
*********************************************/
bool Game::isMouseinGame()
{
    if( sf::Mouse::getPosition(window).x > 0
        && sf::Mouse::getPosition(window).y > 0
        && sf::Mouse::getPosition(window).x < NUM_BOX_WIDTH * BOX_SIZE
        && sf::Mouse::getPosition(window).y < NUM_BOX_HEIGHT * BOX_SIZE)
    {
         return true;
    }
    return false;
}

