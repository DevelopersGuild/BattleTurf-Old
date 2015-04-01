#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include<SFML/Graphics.hpp>


class Box
{
    //friend class Box;
private:
    int owner;  //0 = player1; 1 = player2; 2 = player3; 3 = player4; 4 = wall; 5 = no owner
    int score;  //score range : 3~30
    sf::RectangleShape rect;

    void capture_Indirectly_by(Box *box);
    void fortify();

public:
    Box();
    Box(int size);
    Box(int size, int thickness);
    bool capture_directly_by(int num, int scorenum);
    bool check(Box *box);


    void setscore(int num){score = num;}
    void setrect(int size, int position_x, int position_y,int thickness);

    int getowner(){return owner;}
    int getscore(){return score;}

    void show(sf::RenderWindow *window);
    void setPosition(float x,float y);
    void setFillColor(sf::Color color);
    void setwall();
};

#endif // BOX_H_INCLUDED
