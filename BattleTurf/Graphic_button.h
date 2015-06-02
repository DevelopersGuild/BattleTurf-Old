#ifndef GRAPHIC_BUTTON_H_INCLUDED
#define GRAPHIC_BUTTON_H_INCLUDED

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
    
    sf::Texture textureFocus;
    sf::Texture texture;
    
    bool thereIsText = true; //This is boolean to indicate whether there is text to be drawn. The defaualt is true, so the text will be drawn. Any idea to do it better?

public:
    Graphic_button();
    Graphic_button(sf::Font *font);
    Graphic_button(float length, float height, int x, int y, std::string image, std::string imageFocus); //This is for button with image. Here, the thereIsText will be set to false
    
    Graphic_button(float length, float height, int x, int y, sf::Font* fontPtr); //This is for button with text
    
    
    void setString(sf::String str){text.setString(str);}

    bool isCursor_On_button(const sf::Vector2i &mouseposition);
    void addInto(sf::RenderWindow* windowPtr);
};

#endif // GRAPHIC_BUTTON_H_INCLUDED
