#include "Hillary.hh"


const int Hillary::_degats = 30;


Hillary::Hillary()
{
    if(!o_text.loadFromFile("img/Hillary1.png"))
    {
        std::cout << "Probleme de chargement" << std::endl;
    }
    o_text.setSmooth(true);
    o_sprite.setTexture(o_text);
    o_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));//On place le personnage en haut a gauche de la fenetre

    _x = 0;
    _y = 0;
    o_sprite.setPosition(sf::Vector2f(_x,_y));
    o_rect = o_sprite.getGlobalBounds();
}
void Hillary::updateImage(sf::Clock& HillaryClock)
{
    static int tete = 2;
    std::stringstream nombis;
    std::string nom;
    //On change l'image d'Hillary toutes les 3 secondes avec l'image suivante
    if(HillaryClock.getElapsedTime().asMilliseconds() >= 3000)
    {
        nombis << "img/Hillary" <<tete<<".png";
        nom = nombis.str();
        HillaryClock.restart();
        tete++;
        if(tete == 5)
            tete=1;
        setSprite(nom);
    }
}
//Charge une image ave le nom nom
void Hillary::setSprite(const std::string nom)
{
    o_text.loadFromFile(nom);
    o_sprite.setTexture(o_text);
    o_sprite.setTextureRect(sf::IntRect(0, 0, 70, 86));
}
void Hillary::collision(Joueur& J1, int& anim)
{
    //S'il y une intersection, Hillary enleve degats points de vie et apparait autre part
    if(J1.getRect().intersects(o_rect))
    {
        J1.addPV(-_degats);
        o_sprite.setPosition(sf::Vector2f(rand() % 400 + 20, rand() % 400 + 20));
        o_rect = o_sprite.getGlobalBounds();
    }

}

void Hillary::deplacement(Joueur& J1)
{
    //Se deplace avec une vitesse de 1.2 et se dirige vers le joueur
    float deplacementX = 0;
    float deplacementY = 0;
    static bool updateCoord = false;
    const float vitesse = 1.2;

    //Pour ralentir legerement Hillary sur une ligne droite, qu'elle se deplace d'une coordonnee a la fois
    //Simplifie legerement le jeu
    if(updateCoord)
    {
        if(J1.getSprite().getPosition().x > o_sprite.getPosition().x)
            deplacementX = vitesse;
        else
            deplacementX = -vitesse;
    }
    else
    {
        if(J1.getSprite().getPosition().y > o_sprite.getPosition().y)
            deplacementY = vitesse;
        else
            deplacementY = -vitesse;
    }
    updateCoord = !updateCoord;
    o_sprite.move(deplacementX,deplacementY);
    o_rect = o_sprite.getGlobalBounds();

}
