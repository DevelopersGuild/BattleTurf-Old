#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>

class Graphic_button : public sf::RectangleShape
{
private:
    float length;
    float height;
    int xPos;
    int yPos;
    sf::Font *fontptr;
    sf::Text text;  //text on the button
    sf::Vector2i position;

public:
    Graphic_button();
    Graphic_button(sf::Font *font);
    Graphic_button(float length, float height, int x, int y);
    void setString(sf::String str){text.setString(str);}

    bool isCursor_On_button(const sf::Vector2i &mouseposition);
    void addInto(sf::RenderWindow* windowPtr);
};

#endif // BUTTON_H_INCLUDED
