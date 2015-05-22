/***********************************************
Box Class
The box has 3 states:
0 = non occupied,
1 = occupied
2 = wall
This is held in variable "boxstate"

The box remember its owner by a pointer "owner" which is pointing to a player class.
***********************************************/
#include "box.h"
/*********************************************
Constructor
**********************************************/
Box::Box()
{
    boxstate = non_occupied;
    score = 0;
    rect.setSize(sf::Vector2f(50,50));
    rect.setPosition(0,0);
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2);
}
/*********************************************
setrect function
change the settings of the rectangle.
**********************************************/
void Box::setrect(int size, int position_x, int position_y,int thickness)
{
    rect.setSize(sf::Vector2f(size,size));
    rect.setPosition(position_x,position_y);
    rect.setOutlineThickness(thickness);
}
/*********************************************
show function
Ask window to draw the box.
**********************************************/
void Box::show(sf::RenderWindow *window)
{
    window->draw(rect);
}
/*********************************************
setPosition function
set the position of the box
**********************************************/
void Box::setPosition(float x,float y)
{
    rect.setPosition(x,y);
}
/*********************************************
setFillColor function
set the color of the box
**********************************************/
void Box::setFillColor(sf::Color color)
{
    rect.setFillColor(color);
}
/*********************************************
check function
If the box is not a wall or occupied,
determine which player owns it.
Fortify if it is the same player.
Capture if it is another player and the incoming box has a greater score.
**********************************************/
bool Box::check(Box *box)
{
    if(boxstate == occupied)
    {
        if(box->getowner() == owner)
        {
            fortify();
        }
        else if(box->getscore() > score)
        {
            capture_Indirectly_by(box);
        }
        return true;
    }
    return false;
}
/*********************************************
capture_directly_by function
Capture the box and change the color.
Only available if the box is blank.
**********************************************/
bool Box::capture_directly_by(Player &player, int scorenum)
{
    if(boxstate == 0)
    {
        boxstate = occupied;
        score = scorenum;
        owner = &player;
        rect.setFillColor(player.getcolor());
        return true;
    }
    return false;
}
/*********************************************
capture_Indirectly_by function
Change the owner of the box and change the color.
Can only be called by check() function.
**********************************************/
void Box::capture_Indirectly_by(Box *box)
{
    owner = box->getowner();

    rect.setFillColor(owner->getcolor());
}
/*********************************************
fortify function
Add score to the box.
**********************************************/
void Box::fortify()
{
    score += 3;
}
/*********************************************
setwall function
Set the box as wall.
**********************************************/
void Box::setwall()
{
    boxstate = wall;
    rect.setFillColor(sf::Color(224,224,224,25));
}
