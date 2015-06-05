#include "Graphic_button.h"
#include <iostream>
Graphic_button::Graphic_button()
{
}

Graphic_button::Graphic_button(sf::Font *font){
    fontptr = font;
}


Graphic_button::Graphic_button(float inlength, float inheight, int x, int y,const sf::Font* fontPtr)
{
    xPos = x;
    yPos = y;
    length = inlength;
    height = inheight;
    this->setPosition(xPos, yPos);
    this->setFillColor(sf::Color(204, 255, 153));
    this->setSize(sf::Vector2f(length, height));

    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setPosition(xPos+(static_cast<int>(length/15)), yPos+(static_cast<int>(height/5))); //This part has to be changed later, try different numbers, use ratio, don't use direct addition
    text.setFont(*fontPtr);
}


bool Graphic_button::isCursor_On_button(const sf::Vector2i &mouseposition)
{
    if (mouseposition.x >= xPos && mouseposition.x <= xPos+length &&
        mouseposition.y >= yPos && mouseposition.y <= yPos+height){
        return true;
    }
    return false;
}

void Graphic_button::addInto(sf::RenderWindow* windowPtr){
    windowPtr->draw(*this);
    windowPtr->draw(text);
}
