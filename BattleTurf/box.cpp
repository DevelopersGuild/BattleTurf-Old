#include "box.h"
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

void Box::setrect(sf::Vector2f size, int position_x, int position_y,sf::Color color,int thickness)
{
    rect.setSize(size);
    rect.setPosition(position_x,position_y);
    rect.setFillColor(color);
    rect.setOutlineThickness(thickness);
}

void Box::show(sf::RenderWindow *window)
{
    window->draw(rect);
}

void Box::setPosition(float x,float y)
{
    rect.setPosition(x,y);
}

void Box::setFillColor(sf::Color color)
{
    rect.setFillColor(color);
}

bool Box::captureby(int num)
{
    if(owner == 5)
    {
        owner = num;

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
