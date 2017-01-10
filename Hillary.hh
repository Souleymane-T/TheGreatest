#include "Obstacle.hh"
#include <string>
#include <iostream>
#include <sstream>

class Hillary: public Obstacle
{
public:
    Hillary();
    void updateImage(sf::Clock& HillaryClock);
    void setSprite(const std::string nom);
    void collision(Joueur&, int&);
    void deplacement(Joueur& J1);
private:
    static const int _degats;
};
