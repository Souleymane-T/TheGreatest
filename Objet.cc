#include "Objet.hh"

Objet::Objet(int x, int y)
    :Obstacle(x,y)
{
    if(!o_text.loadFromFile("img/bulletin.png"))
    {
        std::cout << "Probleme de chargement" << std::endl;
    }
    o_text.setSmooth(true);
    o_sprite.setTexture(o_text);
    o_sprite.setPosition(sf::Vector2f(_x,_y));
    o_sprite.setTextureRect(sf::IntRect(0,0,25,22));
    o_rect = o_sprite.getGlobalBounds();
}
void Objet::collision(Joueur& J1, int& special)
{
    if(special == 2)
    {
        o_sprite.setPosition(sf::Vector2f(1000, 1000));//On met les objets speciaux en dehors de l'ecran
        updateORect();
        return;
    }

    else if(special == 0)
    {
        addStat(J1);//Fait appel au addStat propre a chaque classe fille
    }//Dans le cas ou special = 1 ou 0, il faut deplacer dans la zone
    o_sprite.setPosition(sf::Vector2f(rand() % 400 + 20, rand() % 400 + 20));
    updateORect();

}
