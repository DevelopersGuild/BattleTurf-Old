#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(550, 550), "Prototype");
    sf::Vector2i mouseposition;

    int lastbox = 0;
    int currentbox;

    //declare 100 rectangle
    sf::RectangleShape recttest[100];
    for(int i = 0; i < 100; i++)
    {
        //change its size to 50x50
        recttest[i].setSize(sf::Vector2f(50.f,50.f));
        //change its position to proper place
        recttest[i].setPosition(55 * (i / 10),(i % 10) * 55);
        //set its outline color
        recttest[i].setOutlineColor(sf::Color::Black);
        //set its outline thickness
        recttest[i].setOutlineThickness(2);
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

                recttest[lastbox].setFillColor(sf::Color::White);

                currentbox = (mouseposition.y / 55) + 10 * (mouseposition.x / 55);

                recttest[currentbox].setFillColor(sf::Color::Cyan);

                lastbox = currentbox;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                recttest[currentbox].setFillColor(sf::Color::Blue);
            }
        }

        window.clear();
        //window.draw(shape);
        for(int i = 0; i < 100; i++)
        {
            window.draw(recttest[i]);
        }

        window.display();
    }

    std::cout << sizeof(sf::Vector2f) << std::endl;
    std::cout << sizeof(int);

    system("pause");
    return 0;
}
