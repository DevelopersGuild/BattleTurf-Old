#include "box.h"
/*********************************************
Constructor
**********************************************/
Box::Box()
{
    owner = 5;
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
    if(owner <= 3)
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
bool Box::capture_directly_by(int num, int scorenum)
{
    if(owner == 5)
    {
        owner = num;
        score = scorenum;

        switch(num)
        {
        case 0: rect.setFillColor(sf::Color::Blue);
                break;
        case 1: rect.setFillColor(sf::Color::Red);
                break;
        case 2: rect.setFillColor(sf::Color::Green);
                break;
        case 3: rect.setFillColor(sf::Color::Yellow);
                break;
        }
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

    switch(owner)
    {
    case 0: rect.setFillColor(sf::Color::Blue);
            break;
    case 1: rect.setFillColor(sf::Color::Red);
            break;
    case 2: rect.setFillColor(sf::Color::Green);
            break;
    case 3: rect.setFillColor(sf::Color::Yellow);
            break;
    }
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
    owner = 4;
    rect.setFillColor(sf::Color::Black);
}
