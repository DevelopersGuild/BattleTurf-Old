#include <SFML/Graphics.hpp>
#include <iostream>
#include "box.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(550, 550), "Prototype");
    sf::Vector2i mouseposition;
    sf::Clock clock;

    int turn = 0;

    //declare 100 rectangle
    Box box[10][10];
    Box *currentbox, *lastbox;
    lastbox = NULL;

   for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            box[i][j].setPosition(55 * i, 55* j);
        }
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
                //get the position of the mouse
                mouseposition = sf::Mouse::getPosition(window);
                //get the current box
                currentbox = &box[mouseposition.x / 55][mouseposition.y / 55];

                if(currentbox != lastbox)
                {
                    if(currentbox->getowner() == 5)
                    {
                        currentbox->setFillColor(sf::Color::Cyan);
                    }

                    if(lastbox !=NULL && lastbox->getowner() == 5)
                    {
                        lastbox->setFillColor(sf::Color::White);
                    }
                    lastbox = currentbox;
                }
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(currentbox->captureby(turn))
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
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10;j++)
            {
                box[i][j].show(&window);
            }
        }

        window.display();
    }
    system("pause");
    return 0;
}


