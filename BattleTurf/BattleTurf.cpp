#include <SFML/Graphics.hpp>
#include <iostream>
#include "box.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(550, 550), "Prototype");
    sf::Vector2i mouseposition;
    sf::Clock clock;

    int lastbox = 0;
    int currentbox;
    int turn = 0;
    bool capture = false;

    //declare 100 rectangle
    Box recttest[100];
   for(int i = 0; i < 100; i++)
    {
        recttest[i].setPosition(55 * (i / 10),(i % 10) * 55);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                mouseposition = sf::Mouse::getPosition(window);

                currentbox = (mouseposition.y / 55) + 10 * (mouseposition.x / 55);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(recttest[currentbox].captureby(turn))
                {
                    if(turn < 3)
                    {
                        turn++;
                    }
                    else
                    {
                        turn = 0;
                    }
                }

            }
        }

        window.clear();
        //window.draw(shape);
        for(int i = 0; i < 100; i++)
        {
            recttest[i].show(&window);
        }

        window.display();
    }

    system("pause");
    return 0;
}
