#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <iostream>
#include "box.h"

const int NUM_WALL = 6;
const int NUM_PLAYER = 4;
const int NUM_BOX_WIDTH = 6;
const int NUM_BOX_HEIGHT = 6;
const int NUM_SCORE_EACH_PLAYER = ((NUM_BOX_WIDTH * NUM_BOX_HEIGHT) - NUM_WALL) / NUM_PLAYER;

void Show_Cursor_CurrentBox(Box *currentbox, Box *lastbox);
void Set_Wall(Box box[][NUM_BOX_HEIGHT], int numofwall);
void Set_Score_Pool(int player_score[][NUM_SCORE_EACH_PLAYER], int turn);
void Check_adjacent(Box *currentbox, Box box[][NUM_BOX_HEIGHT],int turn);

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(NUM_BOX_WIDTH * 55, NUM_BOX_HEIGHT * 55), "Prototype");
    sf::Vector2i mouseposition;
    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text score[NUM_BOX_WIDTH][NUM_BOX_HEIGHT];
    for(int i = 0; i < NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < NUM_BOX_HEIGHT; j++)
        {
            score[i][j].setFont(font);
            score[i][j].setColor(sf::Color::Black);
            score[i][j].setCharacterSize(30);
            score[i][j].setStyle(sf::Text::Regular);
            score[i][j].setString("0");
            score[i][j].setPosition(55 * i, 55 * j);
        }
    }
    int turn = 0;
    int turn_count = 0;

    //declare 100 rectangle
    Box box[NUM_BOX_WIDTH][NUM_BOX_HEIGHT];
    Set_Wall(box, NUM_WALL);
    Box *currentbox, *lastbox;
    lastbox = NULL;

    int player_score[NUM_PLAYER][NUM_SCORE_EACH_PLAYER];
    Set_Score_Pool(player_score, NUM_SCORE_EACH_PLAYER);

   for(int i = 0; i < NUM_BOX_WIDTH; i++)
    {
        for(int j = 0; j < NUM_BOX_HEIGHT; j++)
        {
            box[i][j].setPosition(55 * i, 55 * j);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                //get the position of the mouse
                mouseposition = sf::Mouse::getPosition(window);
                //get the current box
                currentbox = &box[mouseposition.x / 55][mouseposition.y / 55];
                if(currentbox != lastbox)
                {
                    Show_Cursor_CurrentBox(currentbox,lastbox);
                    lastbox = currentbox;
                }
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //next player, or next turn
                if(currentbox->captureby(turn,player_score[turn][turn_count]))
                {
                    char buf[256];
                    sprintf(buf, "%d",  player_score[turn][turn_count]);
                    score[mouseposition.x / 55][mouseposition.y / 55].setString(buf);

                    turn++;
                    if(turn == NUM_PLAYER)
                    {
                        turn = 0;
                        turn_count++;
                    }
                }
            }
        }

        window.clear();
        //window.draw(shape);
        for(int i = 0; i < NUM_BOX_WIDTH; i++)
        {
            for(int j = 0; j < NUM_BOX_HEIGHT;j++)
            {
                box[i][j].show(&window);

                if(box[i][j].getscore() != 0)
                window.draw(score[i][j]);
            }
        }
        window.display();
    }
    system("pause");
    return 0;
}
/*
Show_Cursor_CurrentBox funcion
This funcion changes the color of box when cursor moved to a new box.
*/
void Show_Cursor_CurrentBox(Box *currentbox, Box *lastbox)
{
        //the current box turns cyan
        if(currentbox->getowner() == 5)
        {
            currentbox->setFillColor(sf::Color::Cyan);
        }
        //the lastbox changes to white, if the lastbox is occupied, don't chnange it to white.
        if(lastbox !=NULL && lastbox->getowner() == 5)
        {
            lastbox->setFillColor(sf::Color::White);
        }
}

/*
Set_Wall funcion
Pick some walls and turn it to wall.
THe numofwall variable must be less than the total number of box in the game.
*/
void Set_Wall(Box box[][NUM_BOX_HEIGHT],int numofwall)
{
    int count = 0;
    while(count < numofwall)
    {
        int target1 = rand() % NUM_BOX_WIDTH;
        int target2 = rand() % NUM_BOX_HEIGHT;
        if(box[target1][target2].getowner() != 4)
        {
            box[target1][target2].setwall();
            count++;
        }
    }
}
/*
set score pool funcion
generate score pool, assign to each player with randomized order.
*/
void Set_Score_Pool(int player_score[NUM_PLAYER][NUM_SCORE_EACH_PLAYER],int num)
{
    //Generate score pool here
    for(int i = 0; i < num; i++)
    {
        int randomnum = rand() % 27 + 3;
        for(int j = 0; j < NUM_PLAYER; j++)
        {
            player_score[j][i] = randomnum;
        }
    }
    //assign to each player with randomized order
    for(int i = 0; i < NUM_PLAYER; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            int randomnum1 = rand() % NUM_SCORE_EACH_PLAYER;
            int hold = player_score[i][randomnum1];
            int randomnum2 = rand() % NUM_SCORE_EACH_PLAYER;
            player_score[i][randomnum1] = player_score[i][randomnum2];
            player_score[i][randomnum2] = hold;
        }
    }
}

void Check_adjacent(Box *currentbox, Box box[][NUM_BOX_WIDTH], int turn)
{

}

