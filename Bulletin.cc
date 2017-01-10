#include "Bulletin.hh"

Bulletin::Bulletin(int x, int y, int giveScore)
    :Objet(x,y),_giveScore(giveScore)
{
    if(!o_text.loadFromFile("img/bulletin.png"))
    {
        std::cout << "Probleme de chargement" << std::endl;
    }
    o_text.setSmooth(true);
    o_sprite.setTexture(o_text);
    o_sprite.setPosition(sf::Vector2f(_x,_y));
    o_rect = o_sprite.getGlobalBounds();
}


void Bulletin::addStat(Joueur& J1)
{
    J1.addScore(_giveScore);
    J1.addRecap("Bulletin");
}

void Bulletin::collision(Joueur& J1, int& special)
{
    if(!special)
        addStat(J1);//Si on est dans le mode special avec bonus/malus, on ne rajoute pas d'autres points
    o_sprite.setPosition(sf::Vector2f(rand() % 400 + 20, rand() % 400 + 20));//Replace l'enveloppe aleatoirement
    o_rect = o_sprite.getGlobalBounds();
}
