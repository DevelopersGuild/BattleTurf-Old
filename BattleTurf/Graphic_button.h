#ifndef GRAPHIC_BUTTON_H_INCLUDED
#define GRAPHIC_BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>

class Graphic_button : public sf::RectangleShape
{
private:
    sf::Font *fontptr;
    sf::Text text;  //text on the button
    sf::Vector2i position;

public:
    Graphic_button();
    Graphic_button(sf::Font *font);
    void setString(sf::String str){text.setString(str);}

    bool isCursor_On_button(const sf::Vector2i &mouseposition);
};

#endif // GRAPHIC_BUTTON_H_INCLUDED
