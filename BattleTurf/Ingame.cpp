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
    
    //load box texture
    box_texture.loadFromFile("Texture/box_empty_1_1.png");
    box_texture_wall.loadFromFile("Texture/box_wall_1_1.png");

    //temporary
    player = new Player[ptrgameSetting->NUM_PLAYER];
    
    player[0].setTexture("Texture/box_blue_1_1.png");
    player[1].setTexture("Texture/box_red_1_1.png");
    player[2].setTexture("Texture/box_green_1_1.png");
    player[3].setTexture("Texture/box_yellow_1_1.png");
    
    player[0].setInterfaceTexture("Texture/image_scorebox_blue_19_23.png");
    player[1].setInterfaceTexture("Texture/image_scorebox_red_19_23.png");
    player[2].setInterfaceTexture("Texture/image_scorebox_green_19_23.png");
    player[3].setInterfaceTexture("Texture/image_scorebox_yellow_19_23.png");
    
    focusTexture.loadFromFile("Texture/box_focus_1_1.png");
    
    player[0].setcolor(sf::Color::Blue);
    player[1].setcolor(sf::Color::Red);
    player[2].setcolor(sf::Color::Green);
    player[3].setcolor(sf::Color::Yellow);

    player_order = new Player*[ptrgameSetting->NUM_PLAYER];
    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        player_order[i] = player + i;
    }

    
    //Set the background to white
    background.setSize(sf::Vector2f(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + ptrgameSetting->INTERFACE_SIZE,
                                         ptrgameSetting->NUM_BOX_HEIGHT * ptrgameSetting->BOX_SIZE));
    background.setFillColor(sf::Color::White);

    Graphing_player_score = new sf::Text[4];

    
    //Configure the score box
    scoreBoxTexture = player[0].getInterfaceTexture();
    GraphingRect1.setTexture(&scoreBoxTexture);        //becuase the color of the first player is blue
    
    GraphingRect1.setSize(sf::Vector2f(ptrgameSetting->BOX_SIZE*4, ptrgameSetting->BOX_SIZE * 4.84));      //the size
    GraphingRect1.setPosition(sf::Vector2f(
                                           ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE +
                                           ptrgameSetting->BOX_SIZE,
                                           ptrgameSetting->BOX_SIZE * 0.6));     //the position

    Graphing_scorebox.setFont(*ptrfont);
    Graphing_scorebox.setCharacterSize(100);
    Graphing_scorebox.setStyle(sf::Text::Regular);
    Graphing_scorebox.setColor(sf::Color::Black);
    Graphing_scorebox.setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + (ptrgameSetting->BOX_SIZE * 2.2),
                                  ptrgameSetting->BOX_SIZE * 3.3);

    for(int i = 0; i < ptrgameSetting->NUM_PLAYER; i++)
    {
        Graphing_player_score[i].setFont(*ptrfont);
        Graphing_player_score[i].setColor(sf::Color::Black);
        Graphing_player_score[i].setCharacterSize(ptrgameSetting->BOX_SIZE);
        Graphing_player_score[i].setStyle(sf::Text::Regular);
        Graphing_player_score[i].setString("0");
        Graphing_player_score[i].setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE, ptrgameSetting->INTERFACE_SIZE + i * 20);
    }

    
    
    
    for (int i = 0; i<12; i++){
        for (int j = 0; j<12; j++){
            box[i][j].setSize(ptrgameSetting->BOX_SIZE);
        }
    }

    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT; j++)
        {
            box[i][j].setPosition(ptrgameSetting->BOX_SIZE * i, ptrgameSetting->BOX_SIZE * j);
            box[i][j].setPosition(ptrgameSetting->BOX_SIZE *i, ptrgameSetting->BOX_SIZE * j);
            box[i][j].setTexture(box_texture);
            //setedge
            if(i == 0 || j == 0 || i == ptrgameSetting->NUM_BOX_WIDTH - 1 || j == ptrgameSetting->NUM_BOX_HEIGHT - 1)
            {
                box[i][j].setwall();
                box[i][j].setTexture(box_texture_wall);
            }
            
            box[i][j].Graphing_score.setFont(*ptrfont);
            box[i][j].Graphing_score.setColor(sf::Color::Black);
            box[i][j].Graphing_score.setCharacterSize(ptrgameSetting->BOX_SIZE/2.5);
            box[i][j].Graphing_score.setStyle(sf::Text::Regular);
            box[i][j].Graphing_score.setString("0");
            
            
            box[i][j].Graphing_score.setPosition(ptrgameSetting->BOX_SIZE * i+ (ptrgameSetting->BOX_SIZE/5.8), ptrgameSetting->BOX_SIZE * j + ptrgameSetting->BOX_SIZE/6.2);
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

void Ingame::update()
{
    ptrwindow->clear();
    ptrwindow->draw(background);

    //redraw the map, will be changed when we do the graphics.
    for(int i = 0; i < ptrgameSetting->NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < ptrgameSetting->NUM_BOX_HEIGHT;j++)
        {
            box[i][j].show(ptrwindow);

            if(box[i][j].getscore() != 0){
                if (box[i][j].getscore() < 10){
                    box[i][j].Graphing_score.setPosition(ptrgameSetting->BOX_SIZE * i+ (ptrgameSetting->BOX_SIZE/2.6), ptrgameSetting->BOX_SIZE * j + ptrgameSetting->BOX_SIZE/4.2);
                } else {
                    box[i][j].Graphing_score.setPosition(ptrgameSetting->BOX_SIZE * i+ (ptrgameSetting->BOX_SIZE/3.7), ptrgameSetting->BOX_SIZE * j + ptrgameSetting->BOX_SIZE/4.2);
                }
                ptrwindow->draw(box[i][j].Graphing_score);
            }
        }
    }
    //draw the background behind the text that shows the current player's color and his scorebox
    ptrwindow->draw(GraphingRect1);
    
    //change the background color of the background
    scoreBoxTexture = player_order[current_active_player]->getInterfaceTexture();
    GraphingRect1.setTexture(&scoreBoxTexture);
    
    //show the current scorebox, if statements to adjust the position of the text
    Graphic_int_ToString(player_order[current_active_player]->getscore_order(turn_passed), Graphing_scorebox);
    if (player_order[current_active_player]->getscore_order(turn_passed) < 10){
        Graphing_scorebox.setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + (ptrgameSetting->BOX_SIZE * 2.7),
                                      ptrgameSetting->BOX_SIZE * 3.1);
    } else {
        Graphing_scorebox.setPosition(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + (ptrgameSetting->BOX_SIZE * 2.4),
                                      ptrgameSetting->BOX_SIZE * 3.1);
    }
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
    currentbox = &box[ptrMousePosition->x / ptrgameSetting->BOX_SIZE][ptrMousePosition->y / ptrgameSetting->BOX_SIZE];

    if(currentbox != lastbox)
    {
        //focus box
        if(currentbox->getstate() == 0)
        {
            currentbox->setTexture(focusTexture);
        }
                //the lastbox changes to white, if the lastbox is occupied, don't chnange it to white.
        if(lastbox !=NULL && lastbox->getstate() == 0)
        {
            lastbox->setTexture(box_texture);
        }
        lastbox = currentbox;
    }
}

void Ingame::Event_MouseLeftClicked()
{
    if(isMouseinGame())
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
            box[target1][target2].setTexture(box_texture_wall);
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
    Box *adjacentBox[] = {  currentbox - 1,                                  //up
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

bool Ingame::isMouseinGame()
{

    if( ptrMousePosition->x > 0
        && ptrMousePosition->y > 0
        && ptrMousePosition->x < ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE
        && ptrMousePosition->y < ptrgameSetting->NUM_BOX_HEIGHT * ptrgameSetting->BOX_SIZE)
    {
         return true;
    }
    return false;
}
