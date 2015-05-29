#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include<SFML/Graphics.hpp>
#include "Player.h"

enum Boxstate {non_occupied = 0, occupied = 1, wall = 2};

class Box
{
    //friend class Box;
private:
       //0 = non occupied, 1 = occupied, 2 = wall
    Boxstate boxstate;
    Player *owner;  //a pointer pointing to the owner
    int score;  //score range : 3~30
    sf::RectangleShape rect;

    void capture_Indirectly_by(Box *box);
    void fortify();

public:
    Box();
    Box(int size);
    Box(int size, int thickness);
    bool capture_directly_by(Player &player, int scorenum);
    bool check(Box *box);

    void setscore(int num){score = num;}
    void setrect(int size, int position_x, int position_y,int thickness);

    Player* getowner(){return owner;}
    int getscore(){return score;}
    Boxstate getstate(){return boxstate;}

    void show(sf::RenderWindow *window);
    void setPosition(float x,float y);
    void setFillColor(sf::Color color);
    void setTexture(const sf::Texture &texture){rect.setTexture(&texture,true);}
    void setwall();

    sf::Text Graphing_score;    //the score for graphing only, it doesn't change the game.
};

#endif // BOX_H_INCLUDED
