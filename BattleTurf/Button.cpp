#include "Graphic_button.h"

Graphic_button::Graphic_button()
{
}

Graphic_button::Graphic_button(sf::Font *font){
    fontptr = font;
}


Graphic_button::Graphic_button(float length, float height, int x, int y)
{
    /* JUST TO TEST THE FONT */
    sf::Font *font  = new sf::Font;
    font->loadFromFile("arial.ttf");
    fontptr = font;
    ///////////////

    this->setPosition(xPos, yPos);
    this->setFillColor(sf::Color::Blue);
    this->setSize(sf::Vector2f(length, height));

    //TO TEST THE TEXT, MODIFY LATER
    text.setCharacterSize(24);
    text.setString("ASDASD");
    text.setColor(sf::Color::Black);
    text.setPosition(xPos+10, yPos+10);
    text.setFont(*fontptr);
    ///////
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
