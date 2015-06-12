#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Player
{
private:
    //int *scorebox_order;
    std::vector<int> scorebox_order;
    int score;
    sf::Color Player_color;
    sf::Texture texture;
    sf::Texture interfaceTexture;
    
public:
    Player();

    void setcolor(sf::Color color);
    void setTexture(std::string);
    void setInterfaceTexture(std::string);
    sf::Texture getInterfaceTexture();
    sf::Texture getTexture();
    void resetscore();
    sf::Color getcolor();
    int getscore_order(int num);
    int getscore();
    void addscore(int value);
    void setscorebox_order(int value[], int num_score_each_player);
};

#endif // PLAYER_H_INCLUDED
