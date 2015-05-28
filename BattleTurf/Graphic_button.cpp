#include "Graphic_button.h"

Graphic_button::Graphic_button()
{

}

Graphic_button::Graphic_button(sf::Font *font)
{
    fontptr = font;
}

bool Graphic_button::isCursor_On_button(const sf::Vector2i &mouseposition)
{
    return true;
    //
}
