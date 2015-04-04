#include "Player.h"
/**************************************
Constructor
**************************************/
Player::Player()
{

}
/****************************************
Initialize
dynamic allocate the scorebox_order.

!MUST BE CALLED WHEN PLAYER CLASS IS CREATED!

Basically I don't think this is a good way to initialize the scorebox_order.
Tell me if you guys got a better idea.
*****************************************/
void Player::Initialize(int num_score_each_player)
{
    scorebox_order = new int[num_score_each_player];
}
/*********************************************
getscore_order
return player's score order.
*********************************************/
int Player::getscore_order(int num)
{
    return scorebox_order[num];
}
/*********************************************
getscore
Return that player's score.
*********************************************/
int Player::getscore()
{
    return score;
}
/*********************************************
setcolor
Set that player's color
*********************************************/
void Player::setcolor(sf::Color color)
{
    Player_color = color;
}
/*********************************************
getcolor
Return that player's color.
*********************************************/
sf::Color Player::getcolor()
{
    return Player_color;
}
/*********************************************
resetscore
set that player's score to 0.
*********************************************/
void Player::resetscore()
{
    score = 0;
}
/*********************************************
addscore
add score to that player.
*********************************************/
void Player::addscore(int value)
{
    score += value;
}
/*********************************************
setscorebox_order
set the score order.
*********************************************/
void Player::setscorebox_order(int value[], int num_score_each_player)
{
    for(int i = 0; i < num_score_each_player; i++)
    {
        scorebox_order[i] = value[i];
    }
}
