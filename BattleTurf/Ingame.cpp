#include "Ingame.h"

Ingame::Ingame()
{
    current_active_player = 0;
    turn_passed = 0;
    lastbox = NULL;
}

Ingame::Ingame(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *gameSetting, sf::Font *font)
{
    current_active_player = 0;
    turn_passed = 0;
    lastbox = NULL;
    ptrwindow = window;
    ptrevent = event;
    ptrMousePosition = mouseposition;
    ptrgameSetting = gameSetting;
    ptrfont = font;

    //temporary
    player = new Player[ptrgameSetting->NUM_PLAYER];
    player[0].setcolor(sf::Color::Blue);
    player[1].setcolor(sf::Color::Red);
    player[2].setcolor(sf::Color::Green);
    player[3].setcolor(sf::Color::Yellow);

    player_order = new Player*[ptrgameSetting->NUM_PLAYER];
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        player_order[i] = player + i;
    }

    Graphing_player_score = new sf::Text[4];

    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)          //initializing each element of score[][]
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT; j++)
        {
        }
    }

    GraphingRect1.setFillColor(sf::Color::Blue);         //becuase the color of the first player is blue
    GraphingRect1.setSize(sf::Vector2f(ptrgameSetting->INTERFACE_SIZE, ptrgameSetting->NUM_BOX_HEIGHT * ptrgameSetting->BOX_SIZE / 2));      //the size
    GraphingRect1.setPosition(sf::Vector2f(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + 5, 0));                //the position
    GraphingRect1.setOutlineThickness(5);                //Outline, the "border" of the rectangle
    GraphingRect1.setOutlineColor(sf::Color::Black);     //the color of the outline is black

    Graphing_scorebox.setFont(*ptrfont);
    Graphing_scorebox.setColor(sf::Color::Black);
    Graphing_scorebox.setCharacterSize(60);
    Graphing_scorebox.setStyle(sf::Text::Regular);
    Graphing_scorebox.setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + (ptrgameSetting->INTERFACE_SIZE / 2), ptrgameSetting->INTERFACE_SIZE / 3);

    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        Graphing_player_score[i].setFont(*ptrfont);
        Graphing_player_score[i].setColor(sf::Color::White);
        Graphing_player_score[i].setCharacterSize(30);
        Graphing_player_score[i].setStyle(sf::Text::Regular);
        Graphing_player_score[i].setString("0");
        Graphing_player_score[i].setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE, ptrgameSetting->INTERFACE_SIZE + i * 20);
    }

    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT; j++)
        {
            box[i][j].setPosition(55 *i, 55 * j);
            //setedge
            if(i == 0 || j == 0 || i == ptrgameSetting->NUM_BOX_WIDTH - 1 || j == ptrgameSetting->NUM_BOX_HEIGHT - 1)
            {
                box[i][j].setwall();
            }

            box[i][j].Graphing_score.setFont(*ptrfont);
            box[i][j].Graphing_score.setColor(sf::Color::Black);
            box[i][j].Graphing_score.setCharacterSize(30);
            box[i][j].Graphing_score.setStyle(sf::Text::Regular);
            box[i][j].Graphing_score.setString("0");
            box[i][j].Graphing_score.setPosition(ptrgameSetting->BOX_SIZE * i, ptrgameSetting->BOX_SIZE * j);
        }
    }

    Mech_Set_Score_Pool();
    Mech_Set_Wall();
    Mech_Reset_Player_Scores();
}

Ingame::~Ingame()
{
    delete [] player;
    delete [] Graphing_player_score;
    delete [] player_order;
}
/*
void Ingame::Init(sf::RenderWindow *window, sf::Event *event, sf::Vector2i *mouseposition, Game_data *gameSetting, sf::Font *font)
{
    ptrwindow = window;
    ptrevent = event;
    ptrMousePosition = mouseposition;
    ptrgameSetting = gameSetting;
    ptrfont = font;

    //temporary
    player = new Player[ptrgameSetting->NUM_PLAYER];
    player[0].setcolor(sf::Color::Blue);
    player[1].setcolor(sf::Color::Red);
    player[2].setcolor(sf::Color::Green);
    player[3].setcolor(sf::Color::Yellow);

    player_order = new Player*[ptrgameSetting->NUM_PLAYER];
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        player_order[i] = player + i;
    }

    Graphing_player_score = new sf::Text[4];

    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)          //initializing each element of score[][]
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT; j++)
        {
        }
    }

    GraphingRect1.setFillColor(sf::Color::Blue);         //becuase the color of the first player is blue
    GraphingRect1.setSize(sf::Vector2f(ptrgameSetting->INTERFACE_SIZE, ptrgameSetting->NUM_BOX_HEIGHT * ptrgameSetting->BOX_SIZE / 2));      //the size
    GraphingRect1.setPosition(sf::Vector2f(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + 5, 0));                //the position
    GraphingRect1.setOutlineThickness(5);                //Outline, the "border" of the rectangle
    GraphingRect1.setOutlineColor(sf::Color::Black);     //the color of the outline is black

    Graphing_scorebox.setFont(*ptrfont);
    Graphing_scorebox.setColor(sf::Color::Black);
    Graphing_scorebox.setCharacterSize(60);
    Graphing_scorebox.setStyle(sf::Text::Regular);
    Graphing_scorebox.setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + (ptrgameSetting->INTERFACE_SIZE / 2), ptrgameSetting->INTERFACE_SIZE / 3);

    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        Graphing_player_score[i].setFont(*ptrfont);
        Graphing_player_score[i].setColor(sf::Color::White);
        Graphing_player_score[i].setCharacterSize(30);
        Graphing_player_score[i].setStyle(sf::Text::Regular);
        Graphing_player_score[i].setString("0");
        Graphing_player_score[i].setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE, ptrgameSetting->INTERFACE_SIZE + i * 20);
    }

    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT; j++)
        {
            box[i][j].setPosition(55 *i, 55 * j);
            //setedge
            if(i == 0 || j == 0 || i == ptrgameSetting->NUM_BOX_WIDTH - 1 || j == ptrgameSetting->NUM_BOX_HEIGHT - 1)
            {
                box[i][j].setwall();
            }

            box[i][j].Graphing_score.setFont(*ptrfont);
            box[i][j].Graphing_score.setColor(sf::Color::Black);
            box[i][j].Graphing_score.setCharacterSize(30);
            box[i][j].Graphing_score.setStyle(sf::Text::Regular);
            box[i][j].Graphing_score.setString("0");
            box[i][j].Graphing_score.setPosition(ptrgameSetting->BOX_SIZE * i, ptrgameSetting->BOX_SIZE * j);
        }
    }

    Mech_Set_Score_Pool();
    Mech_Set_Wall();
    Mech_Reset_Player_Scores();
}
*/
void Ingame::update()
{
    ptrwindow->clear();

    //redraw the map, will be changed when we do the graphics.
    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT;j++)
        {
            box[i][j].show(ptrwindow);

            if(box[i][j].getscore() != 0)
                ptrwindow->draw(box[i][j].Graphing_score);
        }
    }
    //draw the background behind the text that shows the current player's color and his scorebox
    ptrwindow->draw(GraphingRect1);
    //change the background color of the background
    GraphingRect1.setFillColor(player_order[current_active_player]->getcolor());
    //show the current scorebox
    Graphic_int_ToString(player_order[current_active_player]->getscore_order(turn_passed), Graphing_scorebox);
    //draw the scorebox
    ptrwindow->draw(Graphing_scorebox);
    //the total score of each player
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        Graphic_int_ToString(player[i].getscore(),Graphing_player_score[i]);
        ptrwindow->draw(Graphing_player_score[i]);
    }
    ptrwindow->display();
}

void Ingame::HandleEvent()
{
    if (ptrevent->type == sf::Event::Closed)
    {
         ptrwindow->close();
        std::cout << "The winner is Player" << Mech_Find_winner() + 1 << "!" << std::endl;  //debug
    }

    if (ptrevent->type == sf::Event::MouseMoved)
    {
        Event_MouseMoved();
    }

    if(ptrevent->type == sf::Event::MouseButtonPressed)
    {
        Event_MouseLeftClicked();
    }
}

void Ingame::Event_MouseMoved()
{
    //Show_Cursor_Box();
}

void Ingame::Show_Cursor_Box()
{
    //get the current box
    currentbox = &box[ptrMousePosition->x / 55][ptrMousePosition->y / 55];

    if(currentbox != lastbox)
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
        lastbox = currentbox;
    }
}

void Ingame::Event_MouseLeftClicked()
{
    if(currentbox->capture_directly_by(*(player_order[current_active_player]), player_order[current_active_player]->getscore_order(turn_passed)))
    {
        //update the graphing score
        Graphic_int_ToString(player_order[current_active_player]->getscore_order(turn_passed),
                             currentbox->Graphing_score);

        //attack or strengthen the nearby boxes
        Mech_Check_adjacent();

        //count the score, the algorithm is not good and will be changed later
        Mech_Reset_Player_Scores();

        Mech_Calculate_Score();

        Mech_NextPlayer();
    }
}

void Ingame::Mech_NextPlayer()
{
    //next player move
    current_active_player++;
    //if it is the last player of that turn, reset to player1.
    if(current_active_player == ptrgameSetting->NUM_PLAYER)
    {
        Mech_Rearrange_order();
        current_active_player = 0;
        turn_passed++;               //next turn.
    }
}

/*********************************************
Mech_Set_Score_Pool
Randomize the scorebox_order for each player
*********************************************/
void Ingame::Mech_Set_Score_Pool()
{
    int score_pool[ptrgameSetting->NUM_SCORE_EACH_PLAYER];
    //assign to each player with randomized order
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        for(int j = 0; j < ptrgameSetting->NUM_SCORE_EACH_PLAYER; j++)
        {
            score_pool[j] = rand() % 25 + 5;
        }
        player[i].setscorebox_order(score_pool,ptrgameSetting->NUM_SCORE_EACH_PLAYER);
    }
}

/*********************************************
Graphic_int_ToString
convert the integer to sf::Text
This is important when trying to show the score via sf::Text graphic elements.
*********************************************/
void Ingame::Graphic_int_ToString(int value, sf::Text &targettext)
{
    char buf[256];
    sprintf(buf, "%d", value);
    targettext.setString(buf);
}

/*********************************************
Mech_Set_Wall
Randomly pick some tiles and turn them to walls
*********************************************/
void Ingame::Mech_Set_Wall()
{
    int count = 0;
    while(count < ptrgameSetting->NUM_WALL)
    {
        int target1 = rand() % ptrgameSetting->NUM_BOX_WIDTH;
        int target2 = rand() % ptrgameSetting->NUM_BOX_HEIGHT;
        if(box[target1][target2].getstate() != 2)
        {
            box[target1][target2].setwall();
            count++;
        }
    }
}

/*********************************************
Mech_Check_adjacent
"Try" to capture the surrounding tiles.
*********************************************/
void Ingame::Mech_Check_adjacent()
{
    Box *adjacentBox[] = {  currentbox -1,                                  //up
                            currentbox + 1,                                 //down
                            currentbox - ptrgameSetting->NUM_BOX_HEIGHT,    //left
                            currentbox + ptrgameSetting->NUM_BOX_HEIGHT,    //right
                            currentbox - ptrgameSetting->NUM_BOX_HEIGHT - 1,//left top
                            currentbox - ptrgameSetting->NUM_BOX_HEIGHT + 1,//left bottom
                            currentbox + ptrgameSetting->NUM_BOX_HEIGHT - 1,//right top
                            currentbox + ptrgameSetting->NUM_BOX_HEIGHT + 1//right bottom
                            };

    for(int i = 0; i < 8; i++)
    {
        if(adjacentBox[i]->check(currentbox))
        {
            Graphic_int_ToString(adjacentBox[i]->getscore(),adjacentBox[i]->Graphing_score);
        }
    }
}

/*********************************************
Mech_Reset_Player_Scores
Set all player's score to 0.
*********************************************/
void Ingame::Mech_Reset_Player_Scores()
{
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        player[i].resetscore();
    }
}
/*********************************************
Mech_Calculate_Score
GO over the map and calculate the score of each player
*********************************************/
void Ingame::Mech_Calculate_Score()
{
    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)      //go over every box and count the score
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT; j++)
        {

            if( box[i][j].getstate() == 1)        //if somebody occupied the box
            {
                (box[i][j].getowner())->addscore(box[i][j].getscore());
            }
        }
    }
}
/*********************************************
Mech_Find_winner
Find winner. Noted that this function doesn't work if players
have the same score.
*********************************************/
int Ingame::Mech_Find_winner()
{
    int winner = 0;
    for(int i = 1; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        if(player[winner].getscore() < player[i].getscore())
            winner = i;
    }
    return winner;
}
/*********************************************
Mech_Rearrange_order
change the player order, from lowest score to highest score
*********************************************/
void Ingame::Mech_Rearrange_order()
{
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        Player *minimum = player_order[i];
        int target = i;
        for(int j = i + 1; j < ptrgameSetting->NUM_PLAYER; j++)
        {
            if(player_order[j]->getscore() < minimum->getscore())
            {
                minimum = player_order[j];
                target = j;
            }
        }
        player_order[target] = player_order[i];
        player_order[i] = minimum;
    }
}
