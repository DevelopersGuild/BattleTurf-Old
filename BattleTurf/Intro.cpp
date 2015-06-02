#include "Intro.h"
#include <iostream>

Intro::Intro()
{

}

Intro::Intro(sf::RenderWindow *window, Game_data *setting, sf::Font *font)
{
    ptrwindow = window;
    ptrgameSetting = setting;
    ptrfont = font;

    introBackground.setFillColor(sf::Color());
    introBackground.setSize(sf::Vector2f(ptrgameSetting->NUM_BOX_WIDTH * ptrgameSetting->BOX_SIZE + ptrgameSetting->INTERFACE_SIZE,
                                          ptrgameSetting->NUM_BOX_HEIGHT * ptrgameSetting->BOX_SIZE));
    
}

void Intro::Play()
{
    sf::Clock clock;
    sf::Time t1 = sf::milliseconds(6);
    
    sf::Text text("Battle Turf", *ptrfont, 90);
    text.setPosition(250,250);

    //whiten the screen
    for(int i = 1; i < 255; )
    {
        ptrwindow->clear();

         if(clock.getElapsedTime() > t1)
         {
             clock.restart();
             i++;
             introBackground.setFillColor(sf::Color(255,255,255,i));
             text.setColor(sf::Color(0,0,0,i));
         }
        ptrwindow->draw(introBackground);
        ptrwindow->draw(text);
        ptrwindow->display();
    }
    //wait 1 sec
    sf::Time t2 = sf::seconds(1.0);
    clock.restart();
    while(clock.getElapsedTime() < t2)
    {

    }
    //blacken the screen
    for(int i = 1; i < 255; )
    {
        ptrwindow->clear();

         if(clock.getElapsedTime() > t1)
         {
             clock.restart();
             i++;
             introBackground.setFillColor(sf::Color(255,255,255,255 - i));
             text.setColor(sf::Color(0,0,0,255 - i));
         }

        ptrwindow->draw(introBackground);
        ptrwindow->draw(text);

        ptrwindow->display();
    }

}

